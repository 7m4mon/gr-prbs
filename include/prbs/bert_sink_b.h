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

#ifndef INCLUDED_PRBS_BERT_SINK_B_H
#define INCLUDED_PRBS_BERT_SINK_B_H

#include <prbs/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace prbs {

    /*!
     * \brief <+description of block+>
     * \ingroup prbs
     *
     */
    class PRBS_API bert_sink_b : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<bert_sink_b> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of prbs::bert_sink_b.
       *
       * To avoid accidental use of raw pointers, prbs::bert_sink_b's
       * constructor is in a private implementation
       * class. prbs::bert_sink_b::make is the public interface for
       * creating new instances.
       */
      static sptr make(int g_pn_sel, int g_data_invert, int g_total_bits, int g_sync_bits, int g_samp_rate, int g_meas_per_sec);
    };

  } // namespace prbs
} // namespace gr

#endif /* INCLUDED_PRBS_BERT_SINK_B_H */

