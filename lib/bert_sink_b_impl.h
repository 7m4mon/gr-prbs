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

#ifndef INCLUDED_PRBS_BERT_SINK_B_IMPL_H
#define INCLUDED_PRBS_BERT_SINK_B_IMPL_H

#include <prbs/bert_sink_b.h>

namespace gr {
  namespace prbs {

    class bert_sink_b_impl : public bert_sink_b
    {
     private:
      int d_pn_sel;
      int d_data_invert;
      int d_total_bits;
      int d_sync_bits;
      int d_samp_rate;
      int d_meas_per_sec;

     public:
      bert_sink_b_impl(int g_pn_sel, int g_data_invert, int g_total_bits, int g_sync_bits, int g_samp_rate, int g_meas_per_sec);
      ~bert_sink_b_impl();
      int calc_ber();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace prbs
} // namespace gr

#endif /* INCLUDED_PRBS_BERT_SINK_B_IMPL_H */

