#!/bin/bash


mode=$1

#FIXME ADD FUNCTION FOR CHECKING RETURN VALUE AND EXITING
path=.

outdir=$path/.cov_out
objroot=$path/objroot
whereislcov=$path/ext/lcov-1.11/bin

rm -rf $outdir
mkdir -p $outdir

echo -ne "Building  ... "
make clean &> /dev/null
make coverage &> /dev/null
status=$?
if [ "$status" != "0" ]; then
	echo "fail"
	exit 1
else
	echo "Ok"
fi

echo -ne "Running tests ... "
$path/utils/runAllTests.sh &> /dev/null
echo "Ok"


genhtmlopt=" --no-function-coverage "
tfs=" --directory $objroot --capture"

echo -ne "Collecting coverage info ... "
a=`$whereislcov/lcov $tfs --no-recursion --output-file $outdir/full_cov.info &> $outdir/full_cov.out`
status=$?
if [ "$status" != "0" ]; then
	echo "fail"
	exit 1
else
	echo "Ok"
fi

echo -ne "Creating report ... "
a=`$whereislcov/genhtml  --demangle-cpp --sort $genhtmlopt --output-directory $outdir $outdir/full_cov.info &> $outdir/genhtml.out`
status=$?
if [ "$status" != "0" ]; then
	echo "fail"
	exit 1
else
	echo "Ok"
fi

echo "See report in $path/.cov_out/index.html"
exit 0

