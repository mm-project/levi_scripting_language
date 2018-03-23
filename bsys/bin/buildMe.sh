#!/bin/bash

root1="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
root2=`dirname $root1`
root3=`dirname $root2`
#root=`dirname $root3`

source $root3/bsys/bin/set_dev_env.sh

cd $BUILD_PATH

chmod 777 -R ./bsys/*
chmod 777 -R ./test/*
chmod 777 -R ./doc/*


#chmod 777 ./test/reg/runRegTests.sh
#chmod 777 ./test/unit/runUnitTests.sh
#chmod 777 ./test/unit/tests/*
#chmod 777 ./bsys/utils/runTests.sh

echo "*******************************************************************************Dependency generation"
make deps
msta=$?
if [ "$msta" != "0" ]; then
	echo "Dependency generation failed."
	exit 1
fi


echo "*******************************************************************************Compilation"
make rebuild
msta=$?
if [ "$msta" != "0" ]; then
	echo "Compilation failed"
	exit 1
fi

echo "*******************************************************************************Compilation (unit-tests)"
make unit_tests
musta=$?
if [ "$musta" != "0" ]; then
	echo "Unit-test compilation failed"
	exit 1
fi

echo "*******************************************************************************Testing"


runTests.sh
rtsta=$?
#if [ "$rtsta" != "0" ]; then
#	sta=1
#fi


echo "*******************************************************************************Making examples"
make examples
msta=$?
if [ "$msta" != "0" ]; then
	echo "Examples compilation failed"
	exit 1
fi

echo "*******************************************************************************Running examples"
#FIXME
#make examples
runExamples.sh
sta=$?

exit $sta
