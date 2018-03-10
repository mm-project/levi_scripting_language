#!/bin/bash

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
path=.

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

