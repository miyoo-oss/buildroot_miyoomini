# Buildroot setup for Miyoo Mini

![status-badge](https://woodpecker.thingy.jp/api/badges/fifteenhex/buildroot_miyoomini/status.svg)

This is not ready for use yet!!

This will brick your device. You have been warned.

### Building

make -jXX

### Flashing

sudo dd if=buildroot/output/images/sdcard.img of=<YOUR_MMC> bs=1M

### Booting

#### boot command 

gpio output 85 1; bootlogo 0 0 0 0 0; mw 1f001cc0 11; gpio out 8 0; sf probe 0;fatload mmc 0 0x22000000 uImage.xz; gpio out 8 1; sleepms 1000; gpio output 4 1; bootm 0x22000000

#### Boot args

console=ttyS0,115200 clk_ignore_unused earlyprintk debug root=/dev/mmcblk0p2 ro rootfstype=squashfs rootwait