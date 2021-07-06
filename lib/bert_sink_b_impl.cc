/* -*- c++ -*- */
/*
 * Copyright 2020 7M4MON.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "bert_sink_b_impl.h"
#include <stdio.h>
#include <stdlib.h>
//#include "pbrs_common.h"

namespace gr {
  namespace prbs {
    
    namespace bert
    {
      int pn_tap[][2] = { /*PN9*/{8,4},/*PN11*/{10,8},/*PN15*/{14,13},/*PN20*/{19,16},/*PN23*/{22,17},/*PN31*/{30,27}};
      bool pn_inv[] = { /*PN9*/false, /*PN11*/false, /*PN15*/true, /*PN20*/false, /*PN23*/true, /*PN31*/false};

      int *bit_stream_a;
      int *bit_stream_b;
      int pn_sel;
      int data_invert;
      int total_bits;
      int sync_bits;
      int samp_rate;
      int meas_per_sec;
      int meas_counter;
      int tap1, tap2;
    }
    using namespace bert;

    bert_sink_b::sptr
    bert_sink_b::make(int g_pn_sel, int g_data_invert, int g_total_bits, int g_sync_bits, int g_samp_rate, int g_meas_per_sec)
    {
      return gnuradio::get_initial_sptr
        (new bert_sink_b_impl(g_pn_sel, g_data_invert, g_total_bits, g_sync_bits, g_samp_rate, g_meas_per_sec));
    }


    /*
     * The private constructor
     */
    bert_sink_b_impl::bert_sink_b_impl(int g_pn_sel, int g_data_invert, int g_total_bits, int g_sync_bits, int g_samp_rate, int g_meas_per_sec)
      : gr::sync_block("bert_sink_b",
              gr::io_signature::make(1, 1, sizeof(int)),
              gr::io_signature::make(0, 0, 0)),
        d_pn_sel(g_pn_sel),
        d_data_invert(g_data_invert),
        d_total_bits(g_total_bits),
        d_sync_bits(g_sync_bits),
        d_samp_rate(g_samp_rate),
        d_meas_per_sec(g_meas_per_sec)
      {
        pn_sel = d_pn_sel;
        data_invert = d_data_invert;
        total_bits = d_total_bits;
        sync_bits = d_sync_bits;
        samp_rate = d_samp_rate;
        meas_per_sec = d_meas_per_sec;
        meas_counter = 0;

        bit_stream_a = (int *)malloc((total_bits+1) * sizeof(int));  /* メモリ領域の確保 */
        memset(bit_stream_a, 0, (total_bits + 1) * sizeof(int));
        bit_stream_b = (int *)malloc(total_bits * sizeof(int));  /* メモリ領域の確保 */
        memset(bit_stream_b, 0, total_bits * sizeof(int));

        
        tap1 = pn_tap[pn_sel][0];
        tap2 = pn_tap[pn_sel][1];
      }

    /*
     * Our virtual destructor.
     */
    bert_sink_b_impl::~bert_sink_b_impl()
    {
      free(bit_stream_a);
      free(bit_stream_b);
    }

    /*
     * Bit error rate 測定処理本体
     */
    int
    bert_sink_b_impl::calc_ber() {
        unsigned int shift_reg;
        unsigned int reg_key;
        unsigned int ex;
        unsigned int err_bits;
        unsigned int max_err_bits;
        unsigned int min_err_bits;
        unsigned int initial_num;
        unsigned int repeat_bits;

        max_err_bits = 0;
        min_err_bits = sync_bits;
        repeat_bits = ((2<<tap1) - 1); //例 : PN9 -> 2 ^ (8 + 1) -1 = 511 

        /* シフトレジスタの初期値はどれが正解かわからないので全部試す */
        for (initial_num = 1; initial_num < repeat_bits; initial_num++) {
            shift_reg = initial_num;
            err_bits = 0;
            for (int j = 0; j < sync_bits; j++) {
                ex = ((shift_reg & ( 1 << tap1)) >> tap1) ^ ((shift_reg & ( 1 << tap2)) >> tap2); 
                shift_reg <<= 1;
                shift_reg |= ex;
                if (ex != bit_stream_b[j]) {
                    err_bits++;
                }
            }
            if (err_bits < min_err_bits) {
                min_err_bits = err_bits;
                reg_key = initial_num;
            }
            if (err_bits > max_err_bits) max_err_bits = err_bits;   //データの符号反転を見つける用
        }

        /* 本測定 */
        err_bits = 0;
        shift_reg = reg_key;
        for (int k = 0; k < total_bits; k++) {
            ex = ((shift_reg & ( 1 << tap1)) >> tap1) ^ ((shift_reg & ( 1 << tap2)) >> tap2); 
            shift_reg <<= 1;
            shift_reg |= ex;
            if (ex != bit_stream_b[k]) {
                err_bits++;
            }
        }

        printf(" reg_key:%x", reg_key);
        printf(" repeat_bits:%d",repeat_bits);
        printf(" tap1:%d",tap1);
        printf(" tap2:%d",tap2);
        printf(" BER:%f", ((float)err_bits/(float)total_bits));
        printf(" TOTAL:%d", total_bits);
        printf(" ERR:%d", err_bits);
        printf(" MAX:%f", ((float)max_err_bits/(float)sync_bits));
        printf("\r\n");
        return 0;
    } /* calc_ber() */

    int
    bert_sink_b_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const int *in = (const int *) input_items[0];

      // Do <+signal processing+>
      for(int i = 0; i < noutput_items; i++) {
        int in_bit = in[i];
        //if (data_invert) {in_bit} == 1 ? 0 : in_bit == 0 ? 1 : in_bit;
        if (in_bit == 0 || in_bit == 1) {
            bit_stream_a[total_bits] = in_bit;      //末尾に追加
            memcpy(&bit_stream_b[0], &bit_stream_a[1], total_bits * sizeof(int)); /* Dst, Src, Size*/
            memcpy(&bit_stream_a[0], &bit_stream_b[0], total_bits * sizeof(int));
        }
        meas_counter++;
        if (meas_counter > int(samp_rate/meas_per_sec)) {
            calc_ber(/*bit_stream_b*/);
            meas_counter = 0;
        }
      }
      // Tell runtime system how many output items we produced.
      return noutput_items;
      
    }

  } /* namespace prbs */
} /* namespace gr */

