#!/bin/bash



declare -x SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
IPL=`stat -c "%s" $SCRIPT_DIR/input/ipl`
IPL_CUST=`stat -c "%s" $SCRIPT_DIR/input/ipl_cust`
MXPT=`stat -c "%s" $SCRIPT_DIR/input/mxpt`

UBOOT=`stat -c "%s" $SCRIPT_DIR/../../../buildroot/output/images/u-boot.img`

#UBOOT=`stat -c "%s" $SCRIPT_DIR/input/uboot`
UBOOT_ENV=`stat -c "%s" $SCRIPT_DIR/input/uboot_env`


# KERNEL=`stat -c "%s" $SCRIPT_DIR/input/kernel`
KERNEL_UNALIGN=`stat -c "%s" $SCRIPT_DIR/../../../buildroot/output/images/kernel.fit`

KERNEL=`printf $(((($KERNEL_UNALIGN / 0x1000) + 1) * 0x1000))`


#ROOTFS=`stat -c "%s" $SCRIPT_DIR/input/rootfs`
ROOTFS_UNALIGN=`stat -c "%s" $SCRIPT_DIR/../../../buildroot/output/images/rootfs.squashfs`
ROOTFS=`printf $(((($ROOTFS_UNALIGN / 0x1000) + 1) * 0x1000))`


KEY_CUST=`stat -c "%s" $SCRIPT_DIR/input/key_cust`
LOGO=`stat -c "%s" $SCRIPT_DIR/input/logo`
MISERVICE=`stat -c "%s" $SCRIPT_DIR/input/miservice`
CUSTOMER=`stat -c "%s" $SCRIPT_DIR/input/customer`
APPCONFIGS=`stat -c "%s" $SCRIPT_DIR/input/appconfigs`

UBOOT_ALIGN=`printf $(((($UBOOT / 0x1000) + 1) * 0x1000))`

declare -x IPL_HEX=0x10000 #`printf "0x%x\n" $IPL`
declare -x IPL_CUST_HEX=0x10000 #`printf "0x%x\n" $IPL_CUST`
declare -x MXPT_HEX=0x10000 #`printf "0x%x\n" $MXPT`
declare -x UBOOT_ENV_HEX=0x2000 #`printf "0x%x\n" $UBOOT_ENV`
declare -x UBOOT_HEX=`printf "0x%x\n" $UBOOT_ALIGN`

declare -x KERNEL_HEX=`printf "0x%x\n" $KERNEL`
declare -x KEY_CUST_HEX=`printf "0x%x\n" $KEY_CUST`
declare -x LOGO_HEX=`printf "0x%x\n" $LOGO`
declare -x ROOTFS_HEX=`printf "0x%x\n" $ROOTFS`
declare -x MISERVICE_HEX=`printf "0x%x\n" $MISERVICE`
declare -x CUSTOMER_HEX=`printf "0x%x\n" $CUSTOMER`
declare -x APPCONFIGS_HEX=`printf "0x%x\n" $APPCONFIGS`


$SCRIPT_DIR/mxpgenerator \
    "$IPL_HEX(IPL),$IPL_CUST_HEX(IPL_CUST),$MXPT_HEX(MXPT),$UBOOT_ENV_HEX(UBOOT_ENV),$UBOOT_HEX(UBOOT)" \
    "$LOGO_HEX(LOGO),$KERNEL_HEX(KERNEL),$ROOTFS_HEX(ROOTFS)" \
    $SCRIPT_DIR/input/mxpt


genimage --config $SCRIPT_DIR/boot.cfg

BOOT=`stat -c "%s" $SCRIPT_DIR/images/boot.img`

declare -x BOOT_HEX=`printf "0x%x\n" $BOOT`

DATA_START=0x4000

rm $SCRIPT_DIR/input/flash_script.txt

echo "build:202305052130" >> $SCRIPT_DIR/input/flash_script.txt
echo "" >> $SCRIPT_DIR/input/flash_script.txt

# First we want to write the main bootloader info to the flash
# This one is done slightly differently than the others, for good reason
# the mxpt can change - and if it does, then we don't know what we're going to write to
echo 'sf probe 0' >> $SCRIPT_DIR/input/flash_script.txt

# Read the boot data from the image into memory
printf "fatload mmc 0 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
printf ' $(SdUpgradeImage) ' >> $SCRIPT_DIR/input/flash_script.txt
echo "$BOOT_HEX $DATA_START" >> $SCRIPT_DIR/input/flash_script.txt

echo 'sf erase 0 ${filesize}' >> $SCRIPT_DIR/input/flash_script.txt

# Write the data in memory into the flash
echo "sf write 0x21000000 0 $BOOT_HEX" >> $SCRIPT_DIR/input/flash_script.txt

# We do this so we can load the new partition table
echo 'mxp t.load' >> $SCRIPT_DIR/input/flash_script.txt

DATA_START=`printf "0x%X" $(($DATA_START + $BOOT_HEX))`

###### LOGO #######

echo 'mxp r.info LOGO' >> $SCRIPT_DIR/input/flash_script.txt
echo 'sf erase ${sf_part_start} ${sf_part_size}' >> $SCRIPT_DIR/input/flash_script.txt

# Read the boot data from the image into memory
printf "fatload mmc 0 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
printf ' $(SdUpgradeImage) ' >> $SCRIPT_DIR/input/flash_script.txt
echo "$LOGO_HEX $DATA_START" >> $SCRIPT_DIR/input/flash_script.txt

printf "sf write 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
printf ' ${sf_part_start} ' >> $SCRIPT_DIR/input/flash_script.txt
echo "$LOGO_HEX" >> $SCRIPT_DIR/input/flash_script.txt

DATA_START=`printf "0x%X\n" $(($DATA_START + $LOGO_HEX))`

###### KERNEL #######

echo 'mxp r.info KERNEL' >> $SCRIPT_DIR/input/flash_script.txt
echo 'sf erase ${sf_part_start} ${sf_part_size}' >> $SCRIPT_DIR/input/flash_script.txt

# Read the boot data from the image into memory
printf "fatload mmc 0 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
printf ' $(SdUpgradeImage) ' >> $SCRIPT_DIR/input/flash_script.txt
echo "$KERNEL_HEX $DATA_START" >> $SCRIPT_DIR/input/flash_script.txt

printf "sf write 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
printf ' ${sf_part_start} ' >> $SCRIPT_DIR/input/flash_script.txt
echo "$KERNEL_HEX" >> $SCRIPT_DIR/input/flash_script.txt

DATA_START=`printf "0x%X\n" $(($DATA_START + $KERNEL_HEX))`

# ###### KEY_CUST #######

# echo 'mxp r.info KEY_CUST' >> $SCRIPT_DIR/input/flash_script.txt
# echo 'sf erase ${sf_part_start} ${sf_part_size}' >> $SCRIPT_DIR/input/flash_script.txt

# # Read the boot data from the image into memory
# printf "fatload mmc 0 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
# printf ' $(SdUpgradeImage) ' >> $SCRIPT_DIR/input/flash_script.txt
# echo "$KEY_CUST_HEX $DATA_START" >> $SCRIPT_DIR/input/flash_script.txt

# printf "sf write 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
# printf ' ${sf_part_start} ' >> $SCRIPT_DIR/input/flash_script.txt
# echo "$KEY_CUST_HEX" >> $SCRIPT_DIR/input/flash_script.txt

# DATA_START=`printf "0x%X\n" $(($DATA_START + $KEY_CUST_HEX))`



###### ROOTFS #######
echo 'mxp r.info ROOTFS' >> $SCRIPT_DIR/input/flash_script.txt
echo 'sf erase ${sf_part_start} ${sf_part_size}' >> $SCRIPT_DIR/input/flash_script.txt

# Read the boot data from the image into memory
printf "fatload mmc 0 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
printf ' $(SdUpgradeImage) ' >> $SCRIPT_DIR/input/flash_script.txt
echo "$ROOTFS_HEX $DATA_START" >> $SCRIPT_DIR/input/flash_script.txt


printf "sf write 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
printf ' ${sf_part_start} ' >> $SCRIPT_DIR/input/flash_script.txt
echo "$ROOTFS_HEX" >> $SCRIPT_DIR/input/flash_script.txt

DATA_START=`printf "0x%X\n" $(($DATA_START + $ROOTFS_HEX))`


# ###### MISERVICE #######
# echo 'mxp r.info MISERVICE' >> $SCRIPT_DIR/input/flash_script.txt
# echo 'sf erase ${sf_part_start} ${sf_part_size}' >> $SCRIPT_DIR/input/flash_script.txt

# # Read the boot data from the image into memory
# printf "fatload mmc 0 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
# printf ' $(SdUpgradeImage) ' >> $SCRIPT_DIR/input/flash_script.txt
# echo "$MISERVICE_HEX $DATA_START" >> $SCRIPT_DIR/input/flash_script.txt


# printf "sf write 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
# printf ' ${sf_part_start} ' >> $SCRIPT_DIR/input/flash_script.txt
# echo "$MISERVICE_HEX" >> $SCRIPT_DIR/input/flash_script.txt

# DATA_START=`printf "0x%X\n" $(($DATA_START + $MISERVICE_HEX))`

# ###### CUSTOMER #######
# echo 'mxp r.info CUSTOMER' >> $SCRIPT_DIR/input/flash_script.txt
# echo 'sf erase ${sf_part_start} ${sf_part_size}' >> $SCRIPT_DIR/input/flash_script.txt

# # Read the boot data from the image into memory
# printf "fatload mmc 0 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
# printf ' $(SdUpgradeImage) ' >> $SCRIPT_DIR/input/flash_script.txt
# echo "$CUSTOMER_HEX $DATA_START" >> $SCRIPT_DIR/input/flash_script.txt


# printf "sf write 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
# printf ' ${sf_part_start} ' >> $SCRIPT_DIR/input/flash_script.txt
# echo "$CUSTOMER_HEX" >> $SCRIPT_DIR/input/flash_script.txt

# DATA_START=`printf "0x%X\n" $(($DATA_START + $CUSTOMER_HEX))`

# ###### APPCONFIGS #######
# echo 'mxp r.info APPCONFIGS' >> $SCRIPT_DIR/input/flash_script.txt
# echo 'sf erase ${sf_part_start} ${sf_part_size}' >> $SCRIPT_DIR/input/flash_script.txt

# # Read the boot data from the image into memory
# printf "fatload mmc 0 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
# printf ' $(SdUpgradeImage) ' >> $SCRIPT_DIR/input/flash_script.txt
# echo "$APPCONFIGS_HEX $DATA_START" >> $SCRIPT_DIR/input/flash_script.txt

# printf "sf write 0x21000000" >> $SCRIPT_DIR/input/flash_script.txt
# printf ' ${sf_part_start} ' >> $SCRIPT_DIR/input/flash_script.txt
# echo "$APPCONFIGS_HEX" >> $SCRIPT_DIR/input/flash_script.txt

# DATA_START=`printf "0x%X\n" $(($DATA_START + $APPCONFIGS_HEX))`

echo "saveenv" >> $SCRIPT_DIR/input/flash_script.txt
echo "saveenv" >> $SCRIPT_DIR/input/flash_script.txt

echo "reset" >> $SCRIPT_DIR/input/flash_script.txt




genimage --config $SCRIPT_DIR/system.cfg

genimage --config $SCRIPT_DIR/upgrade.cfg