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

#ifndef INCLUDED_PRBS_PRBS_COMMON_H
#define INCLUDED_PRBS_PRBS_COMMON_H

namespace gr {
  namespace prbs {
    enum pn {
        PN9,PN11,PN15,PN20,PN23,PN31
    };
    int pn_tap[][2] = { /*PN9*/{8,4},/*PN11*/{10,8},/*PN15*/{14,13},/*PN20*/{19,16},/*PN23*/{22,17},/*PN31*/{30,27}};
    bool pn_inv[] = { /*PN9*/false, /*PN11*/false, /*PN15*/true, /*PN20*/false, /*PN23*/true, /*PN31*/false};

  } // namespace prbs
} // namespace gr

#endif /* INCLUDED_PRBS_PRBS_COMMON_H */
