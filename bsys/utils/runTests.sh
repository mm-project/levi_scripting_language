#!/bin/bash

#FIXME
#export BUILD_PATH=`pwd`
#$p=`pwd`


root1="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
root2=`dirname $root1`
root3=`dirname $root2`
#root=`dirname $root3`

#export BUILD_PATH=$root3
source $root3/bsys/bin/set_dev_env.sh
#echo "BUILD: $BUILD_PATH"


function print_gunavor 
{
	sta=$1
	if [ "$sta" != "0" ]; then
		echo -e "\033[0;31m	 $sta\033[0m"
	else
		echo -e  "\033[0;32m $sta\033[0m"
	fi
}

mode=$1

#FIXME
path=$BUILD_PATH

echo
echo "************************************************"
echo "Running unit-tests"
echo "************************************************"
$path/test/unit/runUnitTests.sh
unit_sta=$?
#if [ "$sta" != "0" ]; then
#	sta=1
#fi
echo "************************************************"

echo
echo "************************************************"
echo "Running regression test-cases"
echo "************************************************"
$path/test/reg/runRegTests.sh
reg_sta=$?
#if [ "$sta" != "0" ]; then
#	sta=`expr $sta + 1`
#fi
echo "************************************************"
final_sta=`expr $unit_sta + $reg_sta`


		
echo
echo
echo
echo
echo "########################################################################"
echo "Testing result:"
echo "########################################################################"
echo -ne "		Unit test failures: "
print_gunavor $unit_sta
echo -ne "		Regression test failures: "
print_gunavor $reg_sta
echo "########################################################################"
exit $final_sta

