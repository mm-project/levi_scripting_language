#!/bin/bash

mode=$1

#FIXME
path=/c/Users/levons/Desktop/git/diploma_levibyte/diploma
out_dir=./reg_output

levi_exe=$path/bin/levi.exe
data_dir=$path/test/reg/data
golden_dir=$path/test/reg/golden



mkdir -p $out_dir
for fn in `ls $data_dir`; do
	testname=`echo $fn| cut -d'.' -f1`
	echo  -ne "		Running test <$testname> : "
    $levi_exe $data_dir/$fn > $out_dir/$testname.out
	if [ "$mode" == "" ]; then
		result=`diff $golden_dir/$testname.out $out_dir/$testname.out &> /dev/null` 
		if [ "$?" != 0 ] || [ "$result" != "" ]; then
			echo "  Fail"
		else
			echo  "	Pass "
		
		fi
	elif [ "$mode" == "regolden" ]; then
		cp $out_dir/$testname.out $golden_dir/$testname.out
	fi
done

rm -rf $out_dir