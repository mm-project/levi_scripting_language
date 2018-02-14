#!/bin/bash

$levi_exe=../../bin/levi

for fn in `ls data`; do
	testname=`echo $fn| cut -d'.' -f1`
    $levi_exe -i data/$fn > output
	a=`diff output ...` 
		
	echo -ne "Test $testname "
    
	cat $fn
	echo Pass
done