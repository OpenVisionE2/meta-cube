# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

KERNELVERSION = "2.6.34"

BOX_BRAND = "cube"

# magic value to avoid flashing an image which was intended to run on different hardware
CREATEIMAGE_MAGIC = "0x00109500"

IMAGEDIR = "flash-image-256"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	e2bmc-dvb-modules-cube \
	"


DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dtsdownmix --with-eac3"

# image name, used for multi boot selection
MULTIBOOT_IMAGE_NAME ?= "${IMAGE_BASENAME}"

# a rootfs size of 192MB should be sufficient (can be overridden by an image)
ROOTFS_SIZE ?= "C000000"

# image name in the zipfile, can be overridden by an image
ZIPFILE_IMAGE_NAME ?= "firmware.img"

IMAGE_DEPENDS_imgzip256 = "createimage-${MACHINE}-native mtd-utils-native"

IMAGE_CMD_imgzip256 = "\
	mkfs.ubifs -r ${IMAGE_ROOTFS} -o ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}_256.ubifs -m 2048 -e 126976 -c 4096; \
	mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
	createimage_${MACHINE} 126976 ${MULTIBOOT_IMAGE_NAME} kernel ${DEPLOY_DIR_IMAGE}/zImage-${MACHINE}.bin 0 0 rootfs ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}_256.ubifs ${ROOTFS_SIZE} 1 > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${ZIPFILE_IMAGE_NAME}; \
	echo ${IMAGE_NAME} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/donate.txt; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
	cd ${DEPLOY_DIR_IMAGE}; \
	zip ${IMAGE_NAME}_256MB.zip ${IMAGEDIR}/*; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubi; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
	rm -Rf ${IMAGEDIR}; \
	"

IMAGE_CMD_prepend = "\
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

IMAGE_DEVICE_TABLES = ""

PREFERRED_VERSION_kernel-module-extrawlan-rtl8192cu = "3.3.0"
PREFERRED_VERSION_wscan = "20130331"

PREFERRED_PROVIDER_virtual/kernel = "linux-cube"
PREFERRED_VERSION_linux-cube = "${KERNELVERSION}"

OLDEST_KERNEL = "${KERNELVERSION}"
GCCVERSION_cube = "4.9.4"
GLIBCVERSION_cube = "2.19"
PREFERRED_VERSION_glibc_cube = "2.19"
PREFERRED_VERSION_glibc-initial_cube = "2.19"

GLIBC_EXTRA_OECONF = "--with-tls --with-__thread"

SOC_FAMILY = "pnx8471"
TARGET_ARCH = "arm"
DEFAULTTUNE = "armv7a"
TUNE_FEATURES = "cortexa9 vfp"
require conf/machine/include/tune-cortexa9.inc
require conf/machine/include/soc-family.inc
TUNE_CCARGS += "-mfpu=vfpv3-d16"

IMAGE_FSTYPES ?= "imgzip256"

MACHINE_FEATURES += "alsa hdmicec switchoff textlcd dvbapi5 usbhost oldkernel HDMI SCART RCA wifiusblegacy"

RCNAME = "cube"

DISPLAY_BRAND = "MK-Digital"
