#!/bin/bash
#FIXME INSTALL DIR

root1="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
root2=`dirname $root1`
root3=`dirname $root2`
#root=`dirname $root3`

export BUILD_PATH=$root3
echo "BUILD_PATH: $BUILD_PATH"
install_dir=$BUILD_PATH

export PATH=$install_dir/bin/:$install_dir/test/unit/:$install_dir/doc/examples:$install_dir/doc/examples/bin:$$install_dir/test/reg:$install_dir/test/unit/tests/:$install_dir/bsys/utils:$install_dir/bsys/bin:$PATH
export LD_LIBRARY_PATH=$install_dir/lib/:$LD_LIBRARY_PATH
export LEVI_INTERP_EXENAME="leviInterp"
export LEVI_VM_EXENAME="leviVM"
export LEVI_COMPILER_EXENAME="leviC"



#chmod 777 -R ./bsys/*
#chmod 777 -R ./test/*
#chmod 777 -R ./doc/*