#!/bin/bash

#FIXME this is workaround
#cp ../../../lib/liblevi_interp.so .
export LD_LIBRARY_PATH=../../../lib:$LD_LIBRARY_PATH
./ex1