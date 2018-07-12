#
# (C) Copyright 2017
# Herbert Yuan <yuanjp@hust.edu.cn>

# * SPDX-License-Identifier:	GPL-2.0+
#

obj-y	:= lowlevel_init.o

ifdef CONFIG_SPL_BUILD
obj-y += board-spl.o
else
obj-y += board.o
obj-y += timer.o
endif
