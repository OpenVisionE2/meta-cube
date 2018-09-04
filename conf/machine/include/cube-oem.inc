# We know about rtc
include conf/machine/include/build-extras.inc

# magic value to avoid flashing an image which was intended to run on different hardware
CREATEIMAGE_MAGIC = "0x00109500"

IMAGEDIR = "flash-image-256"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
    e2bmc-dvb-modules-cube \
    "

DVBPROVIDER = "kernel"

MACHINE_EXTRA_RRECOMMENDS += "\
    gstreamer1.0-plugin-dvbmediasink \
    "

include conf/machine/include/autoload-filesystems.inc

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dtsdownmix --with-eac3"

# image name, used for multi boot selection
MULTIBOOT_IMAGE_NAME ?= "${IMAGE_BASENAME}"

# a rootfs size of 192MB should be sufficient (can be overridden by an image)
ROOTFS_SIZE ?= "C000000"

UBI_VOLNAME = "rootfs"

# image name in the zipfile, can be overridden by an image
ZIPFILE_IMAGE_NAME ?= "firmware.img"

IMAGE_DEPENDS_imgzip256 = "createimage-${MACHINE}-native mtd-utils-native"

IMAGE_CMD_imgzip256 = "\
    mkfs.ubifs -r ${IMAGE_ROOTFS} -o ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.rootfs_256.ubifs -m 2048 -e 126976 -c 4096; \
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    createimage_${MACHINE} 126976 ${MULTIBOOT_IMAGE_NAME} kernel ${DEPLOY_DIR_IMAGE}/zImage-${MACHINE}.bin 0 0 rootfs ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.rootfs_256.ubifs ${ROOTFS_SIZE} 1 > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${ZIPFILE_IMAGE_NAME}; \
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${IMAGE_NAME}_256MB.zip ${IMAGEDIR}/*; \
    rm -Rf ${IMAGEDIR}; \
    "

IMAGE_DEVICE_TABLES = ""

PREFERRED_VERSION_samba = "3.%"
PREFERRED_VERSION_wpa-supplicant = "0.5.8"
PREFERRED_VERSION_rtl8192cu = "3.3.0"
PREFERRED_VERSION_libnl = "3.2.24"
PREFERRED_VERSION_libarchive = "3.1.2"
PREFERRED_VERSION_wscan = "20130331"

PREFERRED_PROVIDER_virtual/kernel = "linux-cube"
PREFERRED_VERSION_linux-cube = "2.6.34"

OLDEST_KERNEL = "2.6.34"
GCCVERSION = "4.9.4"
GLIBCVERSION = "2.19"

GLIBC_EXTRA_OECONF = "--with-tls --with-__thread"

SOC_FAMILY = "pnx8471"
TARGET_ARCH = "arm"
DEFAULTTUNE = "armv7a"
TUNE_FEATURES = "cortexa9 vfp"
include conf/machine/include/tune-cortexa9.inc
require conf/machine/include/soc-family.inc
TUNE_CCARGS += "-mfpu=vfpv3-d16"

IMAGE_FSTYPES ?= "imgzip256"

MACHINE_FEATURES += "3dtv alsa hdmicec switchoff textlcd dvbapi5 usbhost wifiusblegacy legacykernel singlecore"
