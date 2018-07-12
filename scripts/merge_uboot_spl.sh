#!/bin/sh -e

UBOOT_BUILD_DIR=$1
IMAGE_DIR=$2

# layout
#
#    SPL       | block 0
#	 PADDING   | block 0: padding to block 0 boundary
#    U-Boot    | block 1, 2, ... (depends on the u-boot.bin size)
#    PADDING   | padding to block boundary

BLOCK=$((128*1024))

SPL=$UBOOT_BUILD_DIR/spl/u-boot-spl.bin
UBOOT=$UBOOT_BUILD_DIR/u-boot.bin
OUTBIN=$IMAGE_DIR/u-boot-spl-merge.bin
TMP=/tmp/tmp$$

cp $SPL $TMP
dd if=/dev/zero bs=$BLOCK count=1 | tr "\000" "\377" >> $TMP
truncate --size=$BLOCK $TMP
cat $UBOOT >> $TMP
dd if=/dev/zero bs=$BLOCK count=1 | tr "\000" "\377" >> $TMP
outsize=$(stat --printf="%s" $TMP)
truncate --size=$((outsize-(outsize % BLOCK))) $TMP
mv $TMP $OUTBIN