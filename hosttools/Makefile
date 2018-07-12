#
# Herbert Yuan <yuanjp@hust.eud.cn>
# 2018/2/4
#
# hosttools Official sites:
# 	http://e2fsprogs.sourceforge.net/
#
# every host tools are built out of tree
# host rules are prefixed with host_ to avoid conflicts with 
# userspace programs
#

HOST_PROGRAMS :=

HOSTTOOLS_INSTALL_DIR := $(HOSTTOOLS_BUILD_DIR)/install
HOST_INCLUDE_DIR := $(HOSTTOOLS_INSTALL_DIR)/include
HOST_LIB_DIR := $(HOSTTOOLS_INSTALL_DIR)/lib

# these variables are host tools path
# that build image will use
MKFS-UBIFS := $(HOSTTOOLS_INSTALL_DIR)/sbin/mkfs.ubifs
UBINIZE := $(HOSTTOOLS_INSTALL_DIR)/sbin/ubinize


# the order is important, cuz some packages depends on others
HOST_PROGRAMS += host_zlib host_lzo host_e2fsprogs host_mtdutils

################### zlib #########################
host_zlib_package := zlib-1.2.11
host_zlib_path := $(HOSTTOOLS_DIR)/$(host_zlib_package)
host_zlib_build_path := $(HOSTTOOLS_BUILD_DIR)/$(host_zlib_package)

PHONY += host_zlib host_zlib_clean

host_zlib:
	[ -d $(host_zlib_build_path) ] || mkdir -p $(host_zlib_build_path)
	cd $(host_zlib_build_path) && [ -f Makefile ] || \
		$(host_zlib_path)/configure --prefix=$(HOSTTOOLS_INSTALL_DIR)
	cd $(host_zlib_build_path) && make -j$(JOBS)
	cd $(host_zlib_build_path) && make install

host_zlib_clean:
	rm -fr $(host_zlib_build_path)

################### zlo #########################
host_lzo_package := lzo-2.10
host_lzo_path := $(HOSTTOOLS_DIR)/$(host_lzo_package)
host_lzo_build_path := $(HOSTTOOLS_BUILD_DIR)/$(host_lzo_package)

PHONY += host_lzo host_lzo_clean

host_lzo:
	[ -d $(host_lzo_build_path) ] || mkdir -p $(host_lzo_build_path)
	cd $(host_lzo_build_path) && [ -f Makefile ] || \
		$(host_lzo_path)/configure --prefix=$(HOSTTOOLS_INSTALL_DIR) --enable-shared
	cd $(host_lzo_build_path) && make -j$(JOBS)
	cd $(host_lzo_build_path) && make install

host_lzo_clean:
	rm -fr $(host_lzo_build_path)

################### e2fsprogs #########################
host_e2fsprog_package := e2fsprogs-1.43.8
host_e2fsprog_path := $(HOSTTOOLS_DIR)/$(host_e2fsprog_package)
host_e2fsprog_build_path := $(HOSTTOOLS_BUILD_DIR)/$(host_e2fsprog_package)

PHONY += host_e2fsprogs host_e2fsprogs_clean

host_e2fsprogs:
	[ -d $(host_e2fsprog_build_path) ] || mkdir -p $(host_e2fsprog_build_path)
	cd $(host_e2fsprog_build_path) && [ -f Makefile ] || \
		$(host_e2fsprog_path)/configure --prefix=$(HOSTTOOLS_INSTALL_DIR)
	cd $(host_e2fsprog_build_path) && make -j$(JOBS)
	cd $(host_e2fsprog_build_path) && make install && cd lib/uuid/ && make install
	cd $(host_e2fsprog_build_path) && cd lib/uuid/ && make install

host_e2fsprogs_clean:
	rm -fr $(host_e2fsprog_build_path)

################### zlo #########################
host_mtdutils_package := mtd-utils-2.0.1
host_mtdutils_path := $(HOSTTOOLS_DIR)/$(host_mtdutils_package)
host_mtdutils_build_path := $(HOSTTOOLS_BUILD_DIR)/$(host_mtdutils_package)

PHONY += host_mtdutils host_mtdutils_clean

MTD_DEPENDS += CFLAGS="-I$(HOST_INCLUDE_DIR) -I$(HOST_INCLUDE_DIR)/uuid"
MTD_DEPENDS += LDFLAGS=-L$(HOST_LIB_DIR)
MTD_DEPENDS += LZO_CFLAGS=-I$(HOST_INCLUDE_DIR) LZO_LIBS="-L$(HOST_LIB_DIR) -llzo2"
MTD_DEPENDS += ZLIB_CFLAGS=-I$(HOST_INCLUDE_DIR) ZLIB_LIBS="-L$(HOST_LIB_DIR) -lz"
MTD_DEPENDS += UUID_CFLAGS=-I$(HOST_INCLUDE_DIR) UUID_LIBS="-L$(HOST_LIB_DIR) -luuid"

host_mtdutils:
	[ -d $(host_mtdutils_build_path) ] || mkdir -p $(host_mtdutils_build_path)
	cd $(host_mtdutils_build_path) && [ -f Makefile ] || \
		$(MTD_DEPENDS) $(host_mtdutils_path)/configure --prefix=$(HOSTTOOLS_INSTALL_DIR)
	cd $(host_mtdutils_build_path) && make -j$(JOBS)
	cd $(host_mtdutils_build_path) && make install

host_mtdutils_clean:
	rm -fr $(host_mtdutils_build_path)
