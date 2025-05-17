#!/bin/sh

TARGET=${1:-"*"}
DIR=${2:-sdk}
OUTPUT=${3:-$DIR.zip}

rm -rf $DIR
rm -rf $OUTPUT
mkdir -p $DIR
mkdir -p $DIR/bin
mkdir -p $DIR/lib
mkdir -p $DIR/include

cp engine/LICENSE $DIR/LICENSE.txt

cp -rf engine/include/* $DIR/include/
cp engine/lib/*/$TARGET/*.lib $DIR/lib/
cp bin/*/$TARGET/*.exe ./$DIR/bin/
cp engine/bin/*/$TARGET/*.exe ./$DIR/bin/
cp engine/lib/*/$TARGET/*.dll ./$DIR/bin/

zip -rv $OUTPUT $DIR
rm -rf $DIR
