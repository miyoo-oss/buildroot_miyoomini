# Buildroot setup for Miyoo Mini

![status-badge](https://woodpecker.thingy.jp/api/badges/fifteenhex/buildroot_miyoomini/status.svg)

This is not ready for use yet!!

This will brick your device. You have been warned.

### Current status

1) Does not auto boot, you will need uart to boot up
1) Does not launch retroarch to start, you will need to manually do that
1) Does not play games yet

### Building

make -jXX

### Flashing

There's really a few ways to do this, but if you're coming from stock miyoo stuff - you'll want to get the better uboot 

after building:
1) cd br2miyoomini/package/upgrade_blob
1) ./mxpgenerator_generator.sh
1) cp images/miyoo354_fw.img <YOUR_MMC>/miyoo354_fw.img 

sudo dd if=buildroot/output/images/sdcard.img of=<YOUR_MMC> bs=1M

### Booting

#### boot command 

setenv SdUpgradeImage miyoo354_fw.img;sdstar
i2c dev 0; i2c mw 0x34 0x12.1 0x80 ; bootlogo 0 0 0 0 0; gpio output 4 1; setenv loadaddr 0x22000000; fatload mmc 0:1 ${loadaddr} kernel.fit;bootm ${loadaddr}#midrived06

#### Boot args

console=ttyS0,115200 clk_ignore_unused earlyprintk debug root=/dev/mmcblk0p2 ro rootfstype=squashfs rootwait