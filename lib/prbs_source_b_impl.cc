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
#include "prbs_source_b_impl.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// https://wiki.gnuradio.org/index.php/Guided_Tutorial_GNU_Radio_in_C%2B%2B
//#include "pbrs_common.h"

namespace gr {
  namespace prbs {

    namespace pn_gen {
      enum pn {
        PN9,PN11,PN15,PN20,PN23,PN31
      };
      int pn_tap[][2] = { /*PN9*/{8,4},/*PN11*/{10,8},/*PN15*/{14,13},/*PN20*/{19,16},/*PN23*/{22,17},/*PN31*/{30,27}};
      bool pn_inv[] = { /*PN9*/false, /*PN11*/false, /*PN15*/true, /*PN20*/false, /*PN23*/true, /*PN31*/false};
      unsigned int lfsr, pn_sel, data_invert, tap1, tap2;
      float intent_err_rate;
    }
    using namespace pn_gen;

    prbs_source_b::sptr
    prbs_source_b::make(int g_pn_sel, int g_data_invert, float g_intent_err_rate)  // includeも修正が必要
    {
      return gnuradio::get_initial_sptr
        (new prbs_source_b_impl(g_pn_sel, g_data_invert, g_intent_err_rate));  //ここはintがいらない
    }


    /*
     * The private constructor
     */
    prbs_source_b_impl::prbs_source_b_impl(int g_pn_sel, int g_data_invert, float g_intent_err_rate)
      : gr::sync_block("prbs_source_b",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(int))),
        d_pn_sel(g_pn_sel),
        d_data_invert(g_data_invert),
        d_intent_err_rate(g_intent_err_rate)
    {
      pn_sel = d_pn_sel;
      data_invert = d_data_invert;
      intent_err_rate = d_intent_err_rate;
      lfsr = 0xffffffff;
      tap1 = pn_tap[pn_sel][0];
      tap2 = pn_tap[pn_sel][1];
      srand((unsigned int)time(NULL));
    }

    /*
     * Our virtual destructor.
     */
    prbs_source_b_impl::~prbs_source_b_impl()
    {
    }

    /***************PRBS SOURCE************************/

    int
    prbs_source_b_impl::prbs_gen() {
        unsigned int ex;
        ex = ((lfsr & ( 1 << tap1)) >> tap1) ^ ((lfsr & ( 1 << tap2)) >> tap2); 
        lfsr <<= 1;
        lfsr |= ex;
        if (data_invert) {
          ex = ex ? 0 : 1;
        }
        /*ランダムにエラーを挿入する*/
        if(intent_err_rate > (rand() / (float)RAND_MAX)){
          ex = ex ? 0 : 1;
        } 
        
        return ex;
    }

    int
    prbs_source_b_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      int *out = (int *) output_items[0];

      // Do <+signal processing+>
      for(int i = 0; i < noutput_items; i++) {
        out[i] = prbs_gen();
      }
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace prbs */
} /* namespace gr */

