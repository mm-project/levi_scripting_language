#!/bin/bash

mode=$1

#FIXME
path=$BUILD_PATH

source $path/bsys/bin/set_dev_env.sh
levi_exe=$path/bin/levi
tests_dir=$path/test/unit/tests
out_dir=$path/.tmp/unittest_output

passed=0
total=0
fails=0
fatal_fails=0

mkdir -p $out_dir
cd $out_dir
#FIXME workaround
cp $BUILD_PATH/lib/* ./

for test in `ls $tests_dir`; do
	total=`expr $total + 1`
	testname=`echo $test| cut -d'.' -f1`
	echo  -ne "		Running unit-test <$testname> : "
	
	$tests_dir/$test &> /dev/null
	exit_status=$?
	if [ "$exit_status" != "0" ]; then
		if [ "$exit_status" == "6" ] || [ "$exit_status" == "11" ] ; then
			echo -e "\033[0;31m	CRASH (exit status $exit_status )\033[0m"
			fatal_fails=`expr $fatal_fails + 1`
			continue
		else
			echo -e "\033[0;31m	Fail\033[0m"
			fails=`expr $fails + 1`
			continue	
		fi	
	else
		echo -e  "\033[0;32m	Pass\033[0m"
		passed=`expr $passed + 1`
	fi


done

echo
echo
echo "*************************** UNIT TESTING RESULTS ********************"
if [ "$total" == "0" ]; then
	echo -e "\033[0;31m	NO UNIT TESTS AVAILBLE , please rebuild with <make full> \033[0m"
	echo
	exit 66
fi

fails=`expr $fails + $fatal_fails`
echo "Total:  $total"
echo
echo "Pass:   $passed"
echo "Fail:   $fails    [ Fatal: $fatal_fails ]"
echo "Fatals: $fatal_fails"
echo


#rm -rf $out_dir

#FIXME HACK, if nothing failed than ok :) 
#cd -

exit $fails