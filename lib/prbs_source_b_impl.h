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

// NOT TESTED !!!

#ifndef INCLUDED_PRBS_PRBS_SOURCE_B_IMPL_H
#define INCLUDED_PRBS_PRBS_SOURCE_B_IMPL_H

#include <prbs/prbs_source_b.h>

namespace gr {
  namespace prbs {

    class prbs_source_b_impl : public prbs_source_b
    {
     private:
      // attribute
      int d_pn_sel;
      int d_data_invert;
      float d_intent_err_rate;

     public:
      prbs_source_b_impl(int g_pn_sel, int g_data_invert, float g_intent_err_rate);
      ~prbs_source_b_impl();
      int prbs_gen();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace prbs
} // namespace gr

#endif /* INCLUDED_PRBS_PRBS_SOURCE_B_IMPL_H */

