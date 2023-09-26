################################################################################
#
# RPNG
#
################################################################################

RPNG_VERSION = 4b02b2a26606191bd53054512e36b2881216740e
RPNG_SITE = https://github.com/raysan5/rpng.git
RPNG_SITE_METHOD = git
RPNG_LICENSE = LGPL-2.1
RPNG_INSTALL_STAGING = YES

define RPNG_BUILD_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC) " LD="$(TARGET_LD)" -C $(@D) all
endef

define RPNG_INSTALL_TARGET_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" -C $(@D) DESTDIR=$(TARGET_DIR) install
endef