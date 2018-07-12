#
# Herbert Yuan <yuanjp@hust.eud.cn>
# 2018/1/15
#

# cd here to build
TOP_DIR := $(PWD)
PHONY :=

PHONY += all all_prep
all: all_prep toolchain hosttools uboot kernel kernel_modules_install userspace image
	@$(BUILDTIME) all 1

all_prep:
	@$(BUILDTIME) all 0

# these Makefile should be placed after all
# all should be the first rule
include common.mak
include $(HOSTTOOLS_DIR)/Makefile
include $(USERSPACE_DIR)/Makefile


################### toolchain #########################
PHONY += toolchain

toolchain:


################### hosttools #########################
PHONY += hosttools hosttools_clean

hosttools: $(HOST_PROGRAMS) ;

hosttools_clean:
	rm -fr $(HOSTTOOLS_BUILD_DIR)


################### uboot #########################
PHONY += uboot_prep uboot_defconfig uboot_menuconfig uboot_bakconfig \
		uboot_modelconfig uboot_spl uboot uboot_merge_spl \
		uboot_cscope uboot_clean

UBOOT_ENV := cd $(UBOOT_DIR) && CROSS_COMPILE=$(TOOLCHAIN_BIN_PREFIX) \
			make O=$(UBOOT_BUILD_DIR)/

uboot_prep:
	[ -d $(UBOOT_BUILD_DIR) ] || mkdir -p $(UBOOT_BUILD_DIR)

uboot_defconfig: uboot_prep
	$(UBOOT_ENV) jz2440_defconfig

uboot_menuconfig: uboot_prep
	$(UBOOT_ENV) menuconfig

uboot_bakconfig: 
	cp $(UBOOT_BUILD_DIR)/.config $(TARGET_DIR)/uboot.config

uboot_modelconfig: uboot_prep
	cp $(TARGET_DIR)/uboot.config $(UBOOT_BUILD_DIR)/.config 

uboot_spl: uboot_modelconfig 
	$(UBOOT_ENV) -j$(JOBS) spl/u-boot-spl.bin

uboot: uboot_modelconfig
	@$(BUILDTIME) $@ 0
	$(UBOOT_ENV) -j$(JOBS)
	@$(BUILDTIME) $@ 1

uboot_cscope:
	cd $(UBOOT_DIR) ; \
	find -L ./arch/arm/ ./board/jz2440 ./cmd ./common \
		./disk ./drivers ./env ./fs ./lib ./net ./include -name '*.[chS]' -print > \
		cscope.files; \
	cscope -b -q -k

uboot_clean:
	rm -fr $(UBOOT_BUILD_DIR)


################### kernel #########################
PHONY += kernel_prep kernel_defconfig kernel_menuconfig kernel_bakconfig \
		kernel_modelconfig kernel kernel_cscope kernel_clean

KERNEL_ENV := cd $(KERNEL_DIR) && ARCH=$(ARCH) CROSS_COMPILE=$(TOOLCHAIN_BIN_PREFIX) \
				make O=$(KERNEL_BUILD_DIR)/

kernel_prep:
	[ -d $(KERNEL_BUILD_DIR) ] || mkdir -p $(KERNEL_BUILD_DIR)

kernel_defconfig: kernel_prep
	$(KERNEL_ENV) s3c2410_defconfig

kernel_menuconfig: kernel_prep
	$(KERNEL_ENV) menuconfig

kernel_bakconfig:
	cp $(KERNEL_BUILD_DIR)/.config $(TARGET_DIR)/kernel.config

kernel_modelconfig: kernel_prep
	cp $(TARGET_DIR)/kernel.config $(KERNEL_BUILD_DIR)/.config

kernel: kernel_modelconfig
	@$(BUILDTIME) $@ 0
	$(KERNEL_ENV) -j$(JOBS)
	@$(BUILDTIME) $@ 1

kernel_modules_install:
	rm -fr $(KERNEL_MODULES_INSTALL_DIR)
	$(KERNEL_ENV) INSTALL_MOD_STRIP=1 INSTALL_MOD_PATH=$(KERNEL_MODULES_INSTALL_DIR) modules_install

kernel_dtb:
	$(KERNEL_ENV) $(CONFIG_DTB_NAME)

kernel_cscope:
	$(KERNEL_ENV) cscope

kernel_clean:
	rm -fr $(KERNEL_BUILD_DIR)


################### userspace #########################
PHONY += userspace_prep userspace userspace_clean

userspace_prep:
	@$(BUILDTIME) userspace 0
	[ -d $(USERSPACE_BUILD_DIR) ] || mkdir -p $(USERSPACE_BUILD_DIR)

userspace: userspace_prep $(PROGRAMS)
	@$(BUILDTIME) $@ 1

userspace_clean:
	rm -fr $(USERSPACE_BUILD_DIR)


################### rootfs #########################
PHONY += build_fs_libc rootfs_prep fs_libc fs_build fs_common fs_target \
		rootfs rootfs_clean

glibc_libs := ld-*.so ld-linux.so.* libc-*.so libc.so* libm-*.so libm.so*
build_fs_libc:
	mkdir -p $(FS_LIBC_DIR)/lib/
	for lib in $(glibc_libs) ; do \
		cp -a $(TOOLCHIAN_SYSROOT_DIR)/lib/$${lib} $(FS_LIBC_DIR)/lib/ ; \
	done

rootfs_prep:
	@$(BUILDTIME) rootfs 0
	$(INSTALL) -d $(ROOTFS_DIR)/lib
	$(INSTALL) -d $(ROOTFS_DIR)/proc
	$(INSTALL) -d $(ROOTFS_DIR)/sys
	$(INSTALL) -d $(ROOTFS_DIR)/dev
	$(INSTALL) -d $(ROOTFS_DIR)/etc
	$(INSTALL) -d $(ROOTFS_DIR)/etc/init.d
	$(INSTALL) -d $(ROOTFS_DIR)/usr/lib

fs_libc:
	@$(INSTALL_DIR) $(FS_LIBC_DIR)/ $(ROOTFS_DIR)/

fs_build:
	@$(INSTALL_DIR) $(FS_BUILD_DIR)/ $(ROOTFS_DIR)/ sub

fs_common:
	@$(INSTALL_DIR) $(FS_COMMON_DIR)/ $(ROOTFS_DIR)/

fs_target:
	@$(INSTALL_DIR) $(FS_TARGET_DIR)/ $(ROOTFS_DIR)/

rootfs: rootfs_prep fs_libc fs_build fs_common fs_target
	@$(BUILDTIME) rootfs 1

rootfs_clean:
	rm -fr $(ROOTFS_DIR)

################### kernel image #########################
PHONY += image_prep uImage

image_prep:
	[ -d $(IMAGE_DIR) ] || mkdir -p $(IMAGE_DIR)

$(IMAGE_DIR)/uImage: $(KERNEL_BUILD_DIR)/arch/$(ARCH)/boot/zImage
	$(UBOOT_BUILD_DIR)/tools/mkimage -A $(ARCH) -O linux -T kernel -C none \
       -a 0x30008000 -e 0x30008000 -n Linux -d $< $@ || \
       { [ -f $@ ] && rm $@ ; false; }

uImage: image_prep $(IMAGE_DIR)/uImage ;


################### uboot image #########################
PHONY += uboot_image uboot_merge_spl

$(IMAGE_DIR)/u-boot.bin: $(UBOOT_BUILD_DIR)/u-boot.bin
	cp $< $@

$(IMAGE_DIR)/u-boot-spl.bin: $(UBOOT_BUILD_DIR)/spl/u-boot-spl.bin
	cp $< $@

uboot_merge_spl:
	$(SCRIPT_DIR)/merge_uboot_spl.sh $(UBOOT_BUILD_DIR) $(IMAGE_DIR)

uboot_image: image_prep $(IMAGE_DIR)/u-boot.bin \
	$(IMAGE_DIR)/u-boot-spl.bin uboot_merge_spl

################### rootfs image #########################
PHONY += ubifs image

ubifs:
	fakeroot $(MKFS-UBIFS) -v -r $(ROOTFS_DIR) -F -m 2048 -e 129024 -c 1024 -o $(IMAGE_DIR)/ubifs.img 
	cd $(IMAGE_DIR) && $(UBINIZE) -v -o ubi.img -m 2048 -p 128KiB -s 512 $(TARGET_DIR)/ubinize.cfg

image: image_prep uImage uboot_image rootfs ubifs ;


################### clean #########################
PHONY += clean clean_all

clean: 
	rm -fr $(MODEL_OUTPUT_DIR)

clean_all:
	rm -fr $(OUTPUT_DIR)

.PHONY: $(PHONY)