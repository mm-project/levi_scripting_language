#!/bin/bash

#exit 0

root1="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
root2=`dirname $root1`
root3=`dirname $root2`
#root=`dirname $root3`

#exit 
source $root3/bsys/bin/set_dev_env.sh

if  [ ! -d $BUILD_PATH/bsys/etc/projects.lst ]; then
	echo "Error: $BUILD_PATH/bsys/etc/projects.lst Not found"
	exit 1
fi

for e in `cat $BUILD_PATH/bsys/etc/projects.lst`; do
	
	prj=`echo $e | cut -d':' -f1`
	exe=`echo $e | cut -d':' -f2`
	#echo $prj
	#continue

	#echo "<$prj>"
	if [ "$prj" != "" ]; then
		mkdir -p $BUILD_PATH/include/$prj
		echo "create include dir: $BUILD_PATH/include/$prj"
		cd $BUILD_PATH/include/$prj &> /dev/null
			#pwd
			#echo "ln -s ../../src/$prj/.*hpp ./"
			#FIXME
			#cp $BUILD_PATH/src/$prj/*.hpp  $BUILD_PATH/include/$prj/
			#echo "<$prj>"
			ln -s ../../src/$prj/*.hpp ./ 
		cd - &> /dev/null
	fi
done

