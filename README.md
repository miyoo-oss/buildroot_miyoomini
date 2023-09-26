# Buildroot setup for Miyoo Mini

![status-badge](https://woodpecker.thingy.jp/api/badges/fifteenhex/buildroot_miyoomini/status.svg)

This is not ready for use yet!!

This will brick your device. You have been warned.

## Current status

1) Does not auto boot, you will need uart to boot up
1) Does not launch retroarch to start, you will need to manually do that
1) Does not play games yet
1) the only way to return to stock is to have "fancy" equipment.
1) this has only been tested on the miyoo mini plus, if someone has a miyoo mini and wants to help, please reach out.
1) buttons in retroarch do not work yet by default. there's some overlay work that needs to happen
1) spiflash does not yet work once you're in linux - so you can't boot a rootfs off of the spiflash
1) brightness does not yet work
1) Improved power management can be had with the axp223, but not yet configured
1) wifi usb is always powered
1) better hardware controls within retroarch

## Building

make -j2

(sometimes building more than 2 breaks things....)

## Flashing

********BE READY TO EXPERIENCE BRICKED DEVICES********

There's really a few ways to do this, but if you're coming from stock miyoo stuff - you'll want to get the better uboot 

after building:
1) cd br2miyoomini/package/upgrade_blob
1) ./mxpgenerator_generator.sh
1) cp images/miyoo354_fw.img <YOUR_MMC>/miyoo354_fw.img 


## Booting

After you've flashed into the system, you'll be greated with a nice uboot prompt shell

### if at any point the mmc card seems to be unreadable, reset the device with reset

reset

### To flash new updates:

setenv SdUpgradeImage miyoo354_fw.img;sdstar

### To boot into the kernel located on the spiflash

**THIS DOES NOT WORK RIGHT NOW, LOOK AT THE MMC METHOD BELOW**

setenv bootargs console=ttyS0,115200 clk_ignore_unused earlyprintk debug root=/dev/mtdblock4 ro rootfstype=squashfs rootwait

i2c dev 0; i2c mw 0x34 0x12.1 0x80; bootlogo 0 0 0 0 0; gpio output 4 1; setenv loadaddr 0x22000000; sf probe 0; sf read ${loadaddr} ${sf_kernel_start} ${sf_kernel_size};bootm ${loadaddr}#midrived06

### To boot into the kernel located on the mmc

***Only works after getting the initial flash completed, you need the custom uboot***

1) write the sdcard.img from buildroot/output/images/sdcard.img to your sdcard
1) boot to uboot prompt on device
1) setenv bootargs console=ttyS0,115200 clk_ignore_unused earlyprintk debug root=/dev/mmcblk0p2 ro rootfstype=squashfs rootwait
1) i2c dev 0; i2c mw 0x34 0x12.1 0x80; bootlogo 0 0 0 0 0; gpio output 4 1; setenv loadaddr 0x22000000; fatload mmc 0:1 ${loadaddr} kernel.fit;bootm ${loadaddr}#midrived06