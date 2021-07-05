/* -*- c++ -*- */

#define PRBS_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "prbs_swig_doc.i"

%{
#include "prbs/prbs_source_b.h"
#include "prbs/bert_sink_b.h"
%}

%include "prbs/prbs_source_b.h"
GR_SWIG_BLOCK_MAGIC2(prbs, prbs_source_b);
%include "prbs/bert_sink_b.h"
GR_SWIG_BLOCK_MAGIC2(prbs, bert_sink_b);
