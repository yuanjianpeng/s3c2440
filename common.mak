#
# Herbert Yuan <yuanjp@hust.eud.cn>
# 2018/1/15
#
# Almost every targets are out of tree build
# Almost All build result are in ./output dir
#

KERNEL_DIR := $(TOP_DIR)/linux-4.4.120
UBOOT_DIR := $(TOP_DIR)/u-boot-2017.09
TARGETS_DIR := $(TOP_DIR)/targets
USERSPACE_DIR := $(TOP_DIR)/userspace
HOSTTOOLS_DIR := $(TOP_DIR)/hosttools
SCRIPT_DIR := $(TOP_DIR)/scripts
OUTPUT_DIR = $(TOP_DIR)/output

MODEL_SAVE_FILE := $(OUTPUT_DIR)/.oldmodel

# create output dir
$(shell [ ! -d $(OUTPUT_DIR) ] && mkdir $(OUTPUT_DIR))

ifeq ($(strip $(MODEL)),)
ifeq ($(wildcard $(OUTPUT_DIR)/.oldmodel),)
$(error MODEL undefined)
else
MODEL := $(shell cat $(MODEL_SAVE_FILE))
$(info using cached MODEL $(MODEL))
endif
endif

ifeq ($(wildcard $(TARGET_DIR)/),)
$(error no MODEL $(MODEL))
endif

# save mode to .oldmodel
info_savemode := $(shell if [ ! -f $(MODEL_SAVE_FILE) ] || \
					[ "$(MODEL)" != `cat $(MODEL_SAVE_FILE)` ] ; then \
					echo save MODEL $(MODEL) to $(MODEL_SAVE_FILE); \
					echo $(MODEL) > $(MODEL_SAVE_FILE) ; fi)

ifneq ($(strip $(info_savemode)),)
$(info $(info_savemode))
endif

ifeq ($(JOBS),)
JOBS := $(shell nproc || echo 1)
endif

$(info parallel build using $(JOBS) job)

# BY now MODEL Is valid
#
MODEL_OUTPUT_DIR := $(OUTPUT_DIR)/$(MODEL)
IMAGE_DIR := $(MODEL_OUTPUT_DIR)/image
HOSTTOOLS_BUILD_DIR := $(OUTPUT_DIR)/hosttools
KERNEL_BUILD_DIR := $(MODEL_OUTPUT_DIR)/kernel
UBOOT_BUILD_DIR := $(MODEL_OUTPUT_DIR)/uboot
USERSPACE_BUILD_DIR := $(MODEL_OUTPUT_DIR)/userspace

TARGET_DIR := $(TARGETS_DIR)/$(MODEL)
ROOTFS_DIR := $(IMAGE_DIR)/rootfs
FS_BUILD_DIR := $(IMAGE_DIR)/fs.build
FS_COMMON_DIR := $(TARGETS_DIR)/fs.common
FS_LIBC_DIR := $(TARGET_DIR)/fs.libc
FS_TARGET_DIR := $(TARGET_DIR)/fs.target
KERNEL_MODULES_INSTALL_DIR := $(FS_BUILD_DIR)/kernel_modules

include $(TARGET_DIR)/target.config

CC=${TOOLCHAIN_BIN_PREFIX}-gcc
AS=${TOOLCHAIN_BIN_PREFIX}-as
CPP=${TOOLCHAIN_BIN_PREFIX}-cpp
LD=${TOOLCHAIN_BIN_PREFIX}-ld
STRIP=${TOOLCHAIN_BIN_PREFIX}-strip
OBJDUMP=${TOOLCHAIN_BIN_PREFIX}-objdump
OBJCOPY=${TOOLCHAIN_BIN_PREFIX}-objcopy
READELF=${TOOLCHAIN_BIN_PREFIX}-readelf
RANLIB=${TOOLCHAIN_BIN_PREFIX}-ranlib
SIZE=${TOOLCHAIN_BIN_PREFIX}-size
STIRNGS=${TOOLCHAIN_BIN_PREFIX}-string
AR=${TOOLCHAIN_BIN_PREFIX}-ar
NM=${TOOLCHAIN_BIN_PREFIX}-nm
ADDR2LINE=${TOOLCHAIN_BIN_PREFIX}-addr2line


BUILDTIME := $(SCRIPT_DIR)/buildtime.sh $(OUTPUT_DIR)
INSTALL := install
INSTALL_DIR := $(SCRIPT_DIR)/install_dir.sh