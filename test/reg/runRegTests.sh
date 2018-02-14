#!/bin/bash

mode=$1

#FIXME
path=.

levi_exe=$path/bin/levi
out_dir=$path/reg_output
data_dir=$path/test/reg/data
golden_dir=$path/test/reg/golden



mkdir -p $out_dir
for fn in `ls $data_dir`; do
	testname=`echo $fn| cut -d'.' -f1`
	echo  -ne "		Running test <$testname> : "
    
	a=`$levi_exe $data_dir/$fn &> $out_dir/$testname.out` 
	exit_status=$?
	#echo "$exit_status"
	#continue
	if [ "$exit_status" != "0" ]; then
		echo "	CRASH (exit status $exit_status )"
		continue
	else
		if [ "$mode" == "" ]; then
			if [ ! -f $golden_dir/$testname.golden ];then
				echo "	ERROR - NO GOLDEN"
				continue
			fi
			result=`diff $out_dir/$testname.out  $golden_dir/$testname.golden &> /dev/null` 
			if [ "$?" != 0 ] || [ "$result" != "" ]; then
				echo "	Fail"
			else
				echo  "	Pass"
			fi
		elif [ "$mode" == "regolden" ]; then
			echo "	Regolened"
			cp $out_dir/$testname.out $golden_dir/$testname.golden
		else
			echo "DUMMY!"
		fi
	fi
done

rm -rf $out_dir