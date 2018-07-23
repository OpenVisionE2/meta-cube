SUMMARY = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc

PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "${KV}+${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/cube/cube-drivers-${KV}-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

do_compile() {
}
do_populate_sysroot() {
}

do_install() {
    install -d ${D}/lib/modules/${KV}/extra
    install -d ${D}/${sysconfdir}/modules-load.d
    install -m 0755 ${WORKDIR}/*.ko ${D}/lib/modules/${KV}/extra
    if [ -d ${WORKDIR}/firmware ]; then
        install -d ${D}/lib/firmware
        install -m 0644 ${WORKDIR}/firmware/* ${D}/lib/firmware
    fi
    for i in ${MACHINE}_1 ${MACHINE}_2 ${MACHINE}_3 ${MACHINE}_4; do
        echo $i >> ${D}/${sysconfdir}/modules-load.d/_${MACHINE}.conf
    done
}

FILES_${PN} += "/lib/firmware ${sysconfdir}/modules-load.d/_${MACHINE}.conf /lib/modules/${KV}/extra"
