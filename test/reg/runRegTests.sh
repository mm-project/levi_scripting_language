#!/bin/bash

mode=$1

#FIXME
path=.

source $path/bsys/bin/set_dev_env.sh

levi_exe=$path/bin/levi
out_dir=$path/.tmp/reg_output
data_dir=$path/test/reg/data
golden_dir=$path/test/reg/golden


passed=0
total=0
fails=0
fatal_fails=0
mkdir -p $out_dir
for fn in `ls $data_dir`; do
	total=`expr $total + 1`
	
	testname=`echo $fn| cut -d'.' -f1`
	echo  -ne "		Running test <$testname> : "
    
	a=`$levi_exe $data_dir/$fn &> $out_dir/$testname.out` 
	exit_status=$?
	#echo "$exit_status"
	#continue
	if [ "$exit_status" != "0" ]; then
		echo -e "\033[0;31m	CRASH (exit status $exit_status )\033[0m"
		fatal_fails=`expr $fatal_fails + 1`
		continue
	else
		if [ "$mode" == "" ]; then
			if [ ! -f $golden_dir/$testname.golden ];then
				echo -e "\033[0;31m	ERROR - NO GOLDEN\033[0m"
				fails=`expr $fails + 1`
				continue
			fi
			result=`diff $out_dir/$testname.out  $golden_dir/$testname.golden &> /dev/null` 
			if [ "$?" != 0 ] || [ "$result" != "" ]; then
				echo -e "\033[0;31m	Fail\033[0m"
				fails=`expr $fails + 1`
			else
				echo -e  "\033[0;32m	Pass\033[0m"
				passed=`expr $passed + 1`
			fi
		elif [ "$mode" == "regolden" ]; then
			echo -e "\033[1;33m	Regolened\033[0m"
			cp $out_dir/$testname.out $golden_dir/$testname.golden
			passed=`expr $passed + 1`
		else
			echo -e "\033[1;33m	DUMMY!\033[0m"
			fails=`expr $fails + 1`
		fi
	fi
done

fails=`expr $fails + $fatal_fails`
echo
echo
echo "*************************** REGRESSION TEST RESULTS ********************"
echo "Total:  $total"
echo
echo "Pass:   $passed"
echo "Fail:   $fails    [ Fatal: $fatal_fails ]"
#echo "Fatals: $fatal_fails"
echo


rm -rf $out_dir

#FIXME HACK, if nothing failed than ok :) 
exit $fails