PREFIX = miyoomini
DEFCONFIG=../br2miyoomini/configs/miyoomini_defconfig
EXTERNALS=../br2miyoomini ../br2sanetime ../br2games ../br2directfb2 ../br2chenxing
TOOLCHAIN = arm-buildroot-linux-gnueabihf_sdk-buildroot.tar.gz

.PHONY: all

all: buildroot

include ./br2secretsauce/common.mk
