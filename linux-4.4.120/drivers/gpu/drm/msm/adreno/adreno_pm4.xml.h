#ifndef ADRENO_PM4_XML
#define ADRENO_PM4_XML

/* Autogenerated file, DO NOT EDIT manually!

This file was generated by the rules-ng-ng headergen tool in this git repository:
http://github.com/freedreno/envytools/
git clone https://github.com/freedreno/envytools.git

The rules-ng-ng source files this header was generated from are:
- /home/robclark/src/freedreno/envytools/rnndb/adreno.xml               (    398 bytes, from 2015-09-24 17:25:31)
- /home/robclark/src/freedreno/envytools/rnndb/freedreno_copyright.xml  (   1453 bytes, from 2015-05-20 20:03:07)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/a2xx.xml          (  32901 bytes, from 2015-05-20 20:03:14)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/adreno_common.xml (  10755 bytes, from 2015-09-14 20:46:55)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/adreno_pm4.xml    (  14968 bytes, from 2015-05-20 20:12:27)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/a3xx.xml          (  67771 bytes, from 2015-09-14 20:46:55)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/a4xx.xml          (  63970 bytes, from 2015-09-14 20:50:12)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/ocmem.xml         (   1773 bytes, from 2015-09-24 17:30:00)

Copyright (C) 2013-2015 by the following authors:
- Rob Clark <robdclark@gmail.com> (robclark)

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


enum vgt_event_type {
	VS_DEALLOC = 0,
	PS_DEALLOC = 1,
	VS_DONE_TS = 2,
	PS_DONE_TS = 3,
	CACHE_FLUSH_TS = 4,
	CONTEXT_DONE = 5,
	CACHE_FLUSH = 6,
	HLSQ_FLUSH = 7,
	VIZQUERY_START = 7,
	VIZQUERY_END = 8,
	SC_WAIT_WC = 9,
	RST_PIX_CNT = 13,
	RST_VTX_CNT = 14,
	TILE_FLUSH = 15,
	CACHE_FLUSH_AND_INV_TS_EVENT = 20,
	ZPASS_DONE = 21,
	CACHE_FLUSH_AND_INV_EVENT = 22,
	PERFCOUNTER_START = 23,
	PERFCOUNTER_STOP = 24,
	VS_FETCH_DONE = 27,
	FACENESS_FLUSH = 28,
};

enum pc_di_primtype {
	DI_PT_NONE = 0,
	DI_PT_POINTLIST_PSIZE = 1,
	DI_PT_LINELIST = 2,
	DI_PT_LINESTRIP = 3,
	DI_PT_TRILIST = 4,
	DI_PT_TRIFAN = 5,
	DI_PT_TRISTRIP = 6,
	DI_PT_LINELOOP = 7,
	DI_PT_RECTLIST = 8,
	DI_PT_POINTLIST = 9,
	DI_PT_LINE_ADJ = 10,
	DI_PT_LINESTRIP_ADJ = 11,
	DI_PT_TRI_ADJ = 12,
	DI_PT_TRISTRIP_ADJ = 13,
	DI_PT_PATCHES = 34,
};

enum pc_di_src_sel {
	DI_SRC_SEL_DMA = 0,
	DI_SRC_SEL_IMMEDIATE = 1,
	DI_SRC_SEL_AUTO_INDEX = 2,
	DI_SRC_SEL_RESERVED = 3,
};

enum pc_di_index_size {
	INDEX_SIZE_IGN = 0,
	INDEX_SIZE_16_BIT = 0,
	INDEX_SIZE_32_BIT = 1,
	INDEX_SIZE_8_BIT = 2,
	INDEX_SIZE_INVALID = 0,
};

enum pc_di_vis_cull_mode {
	IGNORE_VISIBILITY = 0,
	USE_VISIBILITY = 1,
};

enum adreno_pm4_packet_type {
	CP_TYPE0_PKT = 0,
	CP_TYPE1_PKT = 0x40000000,
	CP_TYPE2_PKT = 0x80000000,
	CP_TYPE3_PKT = 0xc0000000,
};

enum adreno_pm4_type3_packets {
	CP_ME_INIT = 72,
	CP_NOP = 16,
	CP_INDIRECT_BUFFER = 63,
	CP_INDIRECT_BUFFER_PFD = 55,
	CP_WAIT_FOR_IDLE = 38,
	CP_WAIT_REG_MEM = 60,
	CP_WAIT_REG_EQ = 82,
	CP_WAIT_REG_GTE = 83,
	CP_WAIT_UNTIL_READ = 92,
	CP_WAIT_IB_PFD_COMPLETE = 93,
	CP_REG_RMW = 33,
	CP_SET_BIN_DATA = 47,
	CP_REG_TO_MEM = 62,
	CP_MEM_WRITE = 61,
	CP_MEM_WRITE_CNTR = 79,
	CP_COND_EXEC = 68,
	CP_COND_WRITE = 69,
	CP_EVENT_WRITE = 70,
	CP_EVENT_WRITE_SHD = 88,
	CP_EVENT_WRITE_CFL = 89,
	CP_EVENT_WRITE_ZPD = 91,
	CP_RUN_OPENCL = 49,
	CP_DRAW_INDX = 34,
	CP_DRAW_INDX_2 = 54,
	CP_DRAW_INDX_BIN = 52,
	CP_DRAW_INDX_2_BIN = 53,
	CP_VIZ_QUERY = 35,
	CP_SET_STATE = 37,
	CP_SET_CONSTANT = 45,
	CP_IM_LOAD = 39,
	CP_IM_LOAD_IMMEDIATE = 43,
	CP_LOAD_CONSTANT_CONTEXT = 46,
	CP_INVALIDATE_STATE = 59,
	CP_SET_SHADER_BASES = 74,
	CP_SET_BIN_MASK = 80,
	CP_SET_BIN_SELECT = 81,
	CP_CONTEXT_UPDATE = 94,
	CP_INTERRUPT = 64,
	CP_IM_STORE = 44,
	CP_SET_DRAW_INIT_FLAGS = 75,
	CP_SET_PROTECTED_MODE = 95,
	CP_BOOTSTRAP_UCODE = 111,
	CP_LOAD_STATE = 48,
	CP_COND_INDIRECT_BUFFER_PFE = 58,
	CP_COND_INDIRECT_BUFFER_PFD = 50,
	CP_INDIRECT_BUFFER_PFE = 63,
	CP_SET_BIN = 76,
	CP_TEST_TWO_MEMS = 113,
	CP_REG_WR_NO_CTXT = 120,
	CP_RECORD_PFP_TIMESTAMP = 17,
	CP_WAIT_FOR_ME = 19,
	CP_SET_DRAW_STATE = 67,
	CP_DRAW_INDX_OFFSET = 56,
	CP_DRAW_INDIRECT = 40,
	CP_DRAW_INDX_INDIRECT = 41,
	CP_DRAW_AUTO = 36,
	CP_UNKNOWN_19 = 25,
	CP_UNKNOWN_1A = 26,
	CP_UNKNOWN_4E = 78,
	CP_WIDE_REG_WRITE = 116,
	IN_IB_PREFETCH_END = 23,
	IN_SUBBLK_PREFETCH = 31,
	IN_INSTR_PREFETCH = 32,
	IN_INSTR_MATCH = 71,
	IN_CONST_PREFETCH = 73,
	IN_INCR_UPDT_STATE = 85,
	IN_INCR_UPDT_CONST = 86,
	IN_INCR_UPDT_INSTR = 87,
};

enum adreno_state_block {
	SB_VERT_TEX = 0,
	SB_VERT_MIPADDR = 1,
	SB_FRAG_TEX = 2,
	SB_FRAG_MIPADDR = 3,
	SB_VERT_SHADER = 4,
	SB_GEOM_SHADER = 5,
	SB_FRAG_SHADER = 6,
};

enum adreno_state_type {
	ST_SHADER = 0,
	ST_CONSTANTS = 1,
};

enum adreno_state_src {
	SS_DIRECT = 0,
	SS_INDIRECT = 4,
};

enum a4xx_index_size {
	INDEX4_SIZE_8_BIT = 0,
	INDEX4_SIZE_16_BIT = 1,
	INDEX4_SIZE_32_BIT = 2,
};

#define REG_CP_LOAD_STATE_0					0x00000000
#define CP_LOAD_STATE_0_DST_OFF__MASK				0x0000ffff
#define CP_LOAD_STATE_0_DST_OFF__SHIFT				0
static inline uint32_t CP_LOAD_STATE_0_DST_OFF(uint32_t val)
{
	return ((val) << CP_LOAD_STATE_0_DST_OFF__SHIFT) & CP_LOAD_STATE_0_DST_OFF__MASK;
}
#define CP_LOAD_STATE_0_STATE_SRC__MASK				0x00070000
#define CP_LOAD_STATE_0_STATE_SRC__SHIFT			16
static inline uint32_t CP_LOAD_STATE_0_STATE_SRC(enum adreno_state_src val)
{
	return ((val) << CP_LOAD_STATE_0_STATE_SRC__SHIFT) & CP_LOAD_STATE_0_STATE_SRC__MASK;
}
#define CP_LOAD_STATE_0_STATE_BLOCK__MASK			0x00380000
#define CP_LOAD_STATE_0_STATE_BLOCK__SHIFT			19
static inline uint32_t CP_LOAD_STATE_0_STATE_BLOCK(enum adreno_state_block val)
{
	return ((val) << CP_LOAD_STATE_0_STATE_BLOCK__SHIFT) & CP_LOAD_STATE_0_STATE_BLOCK__MASK;
}
#define CP_LOAD_STATE_0_NUM_UNIT__MASK				0x7fc00000
#define CP_LOAD_STATE_0_NUM_UNIT__SHIFT				22
static inline uint32_t CP_LOAD_STATE_0_NUM_UNIT(uint32_t val)
{
	return ((val) << CP_LOAD_STATE_0_NUM_UNIT__SHIFT) & CP_LOAD_STATE_0_NUM_UNIT__MASK;
}

#define REG_CP_LOAD_STATE_1					0x00000001
#define CP_LOAD_STATE_1_STATE_TYPE__MASK			0x00000003
#define CP_LOAD_STATE_1_STATE_TYPE__SHIFT			0
static inline uint32_t CP_LOAD_STATE_1_STATE_TYPE(enum adreno_state_type val)
{
	return ((val) << CP_LOAD_STATE_1_STATE_TYPE__SHIFT) & CP_LOAD_STATE_1_STATE_TYPE__MASK;
}
#define CP_LOAD_STATE_1_EXT_SRC_ADDR__MASK			0xfffffffc
#define CP_LOAD_STATE_1_EXT_SRC_ADDR__SHIFT			2
static inline uint32_t CP_LOAD_STATE_1_EXT_SRC_ADDR(uint32_t val)
{
	return ((val >> 2) << CP_LOAD_STATE_1_EXT_SRC_ADDR__SHIFT) & CP_LOAD_STATE_1_EXT_SRC_ADDR__MASK;
}

#define REG_CP_DRAW_INDX_0					0x00000000
#define CP_DRAW_INDX_0_VIZ_QUERY__MASK				0xffffffff
#define CP_DRAW_INDX_0_VIZ_QUERY__SHIFT				0
static inline uint32_t CP_DRAW_INDX_0_VIZ_QUERY(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_0_VIZ_QUERY__SHIFT) & CP_DRAW_INDX_0_VIZ_QUERY__MASK;
}

#define REG_CP_DRAW_INDX_1					0x00000001
#define CP_DRAW_INDX_1_PRIM_TYPE__MASK				0x0000003f
#define CP_DRAW_INDX_1_PRIM_TYPE__SHIFT				0
static inline uint32_t CP_DRAW_INDX_1_PRIM_TYPE(enum pc_di_primtype val)
{
	return ((val) << CP_DRAW_INDX_1_PRIM_TYPE__SHIFT) & CP_DRAW_INDX_1_PRIM_TYPE__MASK;
}
#define CP_DRAW_INDX_1_SOURCE_SELECT__MASK			0x000000c0
#define CP_DRAW_INDX_1_SOURCE_SELECT__SHIFT			6
static inline uint32_t CP_DRAW_INDX_1_SOURCE_SELECT(enum pc_di_src_sel val)
{
	return ((val) << CP_DRAW_INDX_1_SOURCE_SELECT__SHIFT) & CP_DRAW_INDX_1_SOURCE_SELECT__MASK;
}
#define CP_DRAW_INDX_1_VIS_CULL__MASK				0x00000600
#define CP_DRAW_INDX_1_VIS_CULL__SHIFT				9
static inline uint32_t CP_DRAW_INDX_1_VIS_CULL(enum pc_di_vis_cull_mode val)
{
	return ((val) << CP_DRAW_INDX_1_VIS_CULL__SHIFT) & CP_DRAW_INDX_1_VIS_CULL__MASK;
}
#define CP_DRAW_INDX_1_INDEX_SIZE__MASK				0x00000800
#define CP_DRAW_INDX_1_INDEX_SIZE__SHIFT			11
static inline uint32_t CP_DRAW_INDX_1_INDEX_SIZE(enum pc_di_index_size val)
{
	return ((val) << CP_DRAW_INDX_1_INDEX_SIZE__SHIFT) & CP_DRAW_INDX_1_INDEX_SIZE__MASK;
}
#define CP_DRAW_INDX_1_NOT_EOP					0x00001000
#define CP_DRAW_INDX_1_SMALL_INDEX				0x00002000
#define CP_DRAW_INDX_1_PRE_DRAW_INITIATOR_ENABLE		0x00004000
#define CP_DRAW_INDX_1_NUM_INSTANCES__MASK			0xff000000
#define CP_DRAW_INDX_1_NUM_INSTANCES__SHIFT			24
static inline uint32_t CP_DRAW_INDX_1_NUM_INSTANCES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_1_NUM_INSTANCES__SHIFT) & CP_DRAW_INDX_1_NUM_INSTANCES__MASK;
}

#define REG_CP_DRAW_INDX_2					0x00000002
#define CP_DRAW_INDX_2_NUM_INDICES__MASK			0xffffffff
#define CP_DRAW_INDX_2_NUM_INDICES__SHIFT			0
static inline uint32_t CP_DRAW_INDX_2_NUM_INDICES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_2_NUM_INDICES__SHIFT) & CP_DRAW_INDX_2_NUM_INDICES__MASK;
}

#define REG_CP_DRAW_INDX_3					0x00000003
#define CP_DRAW_INDX_3_INDX_BASE__MASK				0xffffffff
#define CP_DRAW_INDX_3_INDX_BASE__SHIFT				0
static inline uint32_t CP_DRAW_INDX_3_INDX_BASE(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_3_INDX_BASE__SHIFT) & CP_DRAW_INDX_3_INDX_BASE__MASK;
}

#define REG_CP_DRAW_INDX_4					0x00000004
#define CP_DRAW_INDX_4_INDX_SIZE__MASK				0xffffffff
#define CP_DRAW_INDX_4_INDX_SIZE__SHIFT				0
static inline uint32_t CP_DRAW_INDX_4_INDX_SIZE(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_4_INDX_SIZE__SHIFT) & CP_DRAW_INDX_4_INDX_SIZE__MASK;
}

#define REG_CP_DRAW_INDX_2_0					0x00000000
#define CP_DRAW_INDX_2_0_VIZ_QUERY__MASK			0xffffffff
#define CP_DRAW_INDX_2_0_VIZ_QUERY__SHIFT			0
static inline uint32_t CP_DRAW_INDX_2_0_VIZ_QUERY(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_2_0_VIZ_QUERY__SHIFT) & CP_DRAW_INDX_2_0_VIZ_QUERY__MASK;
}

#define REG_CP_DRAW_INDX_2_1					0x00000001
#define CP_DRAW_INDX_2_1_PRIM_TYPE__MASK			0x0000003f
#define CP_DRAW_INDX_2_1_PRIM_TYPE__SHIFT			0
static inline uint32_t CP_DRAW_INDX_2_1_PRIM_TYPE(enum pc_di_primtype val)
{
	return ((val) << CP_DRAW_INDX_2_1_PRIM_TYPE__SHIFT) & CP_DRAW_INDX_2_1_PRIM_TYPE__MASK;
}
#define CP_DRAW_INDX_2_1_SOURCE_SELECT__MASK			0x000000c0
#define CP_DRAW_INDX_2_1_SOURCE_SELECT__SHIFT			6
static inline uint32_t CP_DRAW_INDX_2_1_SOURCE_SELECT(enum pc_di_src_sel val)
{
	return ((val) << CP_DRAW_INDX_2_1_SOURCE_SELECT__SHIFT) & CP_DRAW_INDX_2_1_SOURCE_SELECT__MASK;
}
#define CP_DRAW_INDX_2_1_VIS_CULL__MASK				0x00000600
#define CP_DRAW_INDX_2_1_VIS_CULL__SHIFT			9
static inline uint32_t CP_DRAW_INDX_2_1_VIS_CULL(enum pc_di_vis_cull_mode val)
{
	return ((val) << CP_DRAW_INDX_2_1_VIS_CULL__SHIFT) & CP_DRAW_INDX_2_1_VIS_CULL__MASK;
}
#define CP_DRAW_INDX_2_1_INDEX_SIZE__MASK			0x00000800
#define CP_DRAW_INDX_2_1_INDEX_SIZE__SHIFT			11
static inline uint32_t CP_DRAW_INDX_2_1_INDEX_SIZE(enum pc_di_index_size val)
{
	return ((val) << CP_DRAW_INDX_2_1_INDEX_SIZE__SHIFT) & CP_DRAW_INDX_2_1_INDEX_SIZE__MASK;
}
#define CP_DRAW_INDX_2_1_NOT_EOP				0x00001000
#define CP_DRAW_INDX_2_1_SMALL_INDEX				0x00002000
#define CP_DRAW_INDX_2_1_PRE_DRAW_INITIATOR_ENABLE		0x00004000
#define CP_DRAW_INDX_2_1_NUM_INSTANCES__MASK			0xff000000
#define CP_DRAW_INDX_2_1_NUM_INSTANCES__SHIFT			24
static inline uint32_t CP_DRAW_INDX_2_1_NUM_INSTANCES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_2_1_NUM_INSTANCES__SHIFT) & CP_DRAW_INDX_2_1_NUM_INSTANCES__MASK;
}

#define REG_CP_DRAW_INDX_2_2					0x00000002
#define CP_DRAW_INDX_2_2_NUM_INDICES__MASK			0xffffffff
#define CP_DRAW_INDX_2_2_NUM_INDICES__SHIFT			0
static inline uint32_t CP_DRAW_INDX_2_2_NUM_INDICES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_2_2_NUM_INDICES__SHIFT) & CP_DRAW_INDX_2_2_NUM_INDICES__MASK;
}

#define REG_CP_DRAW_INDX_OFFSET_0				0x00000000
#define CP_DRAW_INDX_OFFSET_0_PRIM_TYPE__MASK			0x0000003f
#define CP_DRAW_INDX_OFFSET_0_PRIM_TYPE__SHIFT			0
static inline uint32_t CP_DRAW_INDX_OFFSET_0_PRIM_TYPE(enum pc_di_primtype val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_0_PRIM_TYPE__SHIFT) & CP_DRAW_INDX_OFFSET_0_PRIM_TYPE__MASK;
}
#define CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT__MASK		0x000000c0
#define CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT__SHIFT		6
static inline uint32_t CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT(enum pc_di_src_sel val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT__SHIFT) & CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT__MASK;
}
#define CP_DRAW_INDX_OFFSET_0_TESSELLATE			0x00000100
#define CP_DRAW_INDX_OFFSET_0_INDEX_SIZE__MASK			0x00000c00
#define CP_DRAW_INDX_OFFSET_0_INDEX_SIZE__SHIFT			10
static inline uint32_t CP_DRAW_INDX_OFFSET_0_INDEX_SIZE(enum a4xx_index_size val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_0_INDEX_SIZE__SHIFT) & CP_DRAW_INDX_OFFSET_0_INDEX_SIZE__MASK;
}
#define CP_DRAW_INDX_OFFSET_0_TESS_MODE__MASK			0x01f00000
#define CP_DRAW_INDX_OFFSET_0_TESS_MODE__SHIFT			20
static inline uint32_t CP_DRAW_INDX_OFFSET_0_TESS_MODE(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_0_TESS_MODE__SHIFT) & CP_DRAW_INDX_OFFSET_0_TESS_MODE__MASK;
}

#define REG_CP_DRAW_INDX_OFFSET_1				0x00000001
#define CP_DRAW_INDX_OFFSET_1_NUM_INSTANCES__MASK		0xffffffff
#define CP_DRAW_INDX_OFFSET_1_NUM_INSTANCES__SHIFT		0
static inline uint32_t CP_DRAW_INDX_OFFSET_1_NUM_INSTANCES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_1_NUM_INSTANCES__SHIFT) & CP_DRAW_INDX_OFFSET_1_NUM_INSTANCES__MASK;
}

#define REG_CP_DRAW_INDX_OFFSET_2				0x00000002
#define CP_DRAW_INDX_OFFSET_2_NUM_INDICES__MASK			0xffffffff
#define CP_DRAW_INDX_OFFSET_2_NUM_INDICES__SHIFT		0
static inline uint32_t CP_DRAW_INDX_OFFSET_2_NUM_INDICES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_2_NUM_INDICES__SHIFT) & CP_DRAW_INDX_OFFSET_2_NUM_INDICES__MASK;
}

#define REG_CP_DRAW_INDX_OFFSET_3				0x00000003

#define REG_CP_DRAW_INDX_OFFSET_4				0x00000004
#define CP_DRAW_INDX_OFFSET_4_INDX_BASE__MASK			0xffffffff
#define CP_DRAW_INDX_OFFSET_4_INDX_BASE__SHIFT			0
static inline uint32_t CP_DRAW_INDX_OFFSET_4_INDX_BASE(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_4_INDX_BASE__SHIFT) & CP_DRAW_INDX_OFFSET_4_INDX_BASE__MASK;
}

#define REG_CP_DRAW_INDX_OFFSET_5				0x00000005
#define CP_DRAW_INDX_OFFSET_5_INDX_SIZE__MASK			0xffffffff
#define CP_DRAW_INDX_OFFSET_5_INDX_SIZE__SHIFT			0
static inline uint32_t CP_DRAW_INDX_OFFSET_5_INDX_SIZE(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_5_INDX_SIZE__SHIFT) & CP_DRAW_INDX_OFFSET_5_INDX_SIZE__MASK;
}

#define REG_CP_SET_DRAW_STATE_0					0x00000000
#define CP_SET_DRAW_STATE_0_COUNT__MASK				0x0000ffff
#define CP_SET_DRAW_STATE_0_COUNT__SHIFT			0
static inline uint32_t CP_SET_DRAW_STATE_0_COUNT(uint32_t val)
{
	return ((val) << CP_SET_DRAW_STATE_0_COUNT__SHIFT) & CP_SET_DRAW_STATE_0_COUNT__MASK;
}
#define CP_SET_DRAW_STATE_0_DIRTY				0x00010000
#define CP_SET_DRAW_STATE_0_DISABLE				0x00020000
#define CP_SET_DRAW_STATE_0_DISABLE_ALL_GROUPS			0x00040000
#define CP_SET_DRAW_STATE_0_LOAD_IMMED				0x00080000
#define CP_SET_DRAW_STATE_0_GROUP_ID__MASK			0x1f000000
#define CP_SET_DRAW_STATE_0_GROUP_ID__SHIFT			24
static inline uint32_t CP_SET_DRAW_STATE_0_GROUP_ID(uint32_t val)
{
	return ((val) << CP_SET_DRAW_STATE_0_GROUP_ID__SHIFT) & CP_SET_DRAW_STATE_0_GROUP_ID__MASK;
}

#define REG_CP_SET_DRAW_STATE_1					0x00000001
#define CP_SET_DRAW_STATE_1_ADDR__MASK				0xffffffff
#define CP_SET_DRAW_STATE_1_ADDR__SHIFT				0
static inline uint32_t CP_SET_DRAW_STATE_1_ADDR(uint32_t val)
{
	return ((val) << CP_SET_DRAW_STATE_1_ADDR__SHIFT) & CP_SET_DRAW_STATE_1_ADDR__MASK;
}

#define REG_CP_SET_BIN_0					0x00000000

#define REG_CP_SET_BIN_1					0x00000001
#define CP_SET_BIN_1_X1__MASK					0x0000ffff
#define CP_SET_BIN_1_X1__SHIFT					0
static inline uint32_t CP_SET_BIN_1_X1(uint32_t val)
{
	return ((val) << CP_SET_BIN_1_X1__SHIFT) & CP_SET_BIN_1_X1__MASK;
}
#define CP_SET_BIN_1_Y1__MASK					0xffff0000
#define CP_SET_BIN_1_Y1__SHIFT					16
static inline uint32_t CP_SET_BIN_1_Y1(uint32_t val)
{
	return ((val) << CP_SET_BIN_1_Y1__SHIFT) & CP_SET_BIN_1_Y1__MASK;
}

#define REG_CP_SET_BIN_2					0x00000002
#define CP_SET_BIN_2_X2__MASK					0x0000ffff
#define CP_SET_BIN_2_X2__SHIFT					0
static inline uint32_t CP_SET_BIN_2_X2(uint32_t val)
{
	return ((val) << CP_SET_BIN_2_X2__SHIFT) & CP_SET_BIN_2_X2__MASK;
}
#define CP_SET_BIN_2_Y2__MASK					0xffff0000
#define CP_SET_BIN_2_Y2__SHIFT					16
static inline uint32_t CP_SET_BIN_2_Y2(uint32_t val)
{
	return ((val) << CP_SET_BIN_2_Y2__SHIFT) & CP_SET_BIN_2_Y2__MASK;
}

#define REG_CP_SET_BIN_DATA_0					0x00000000
#define CP_SET_BIN_DATA_0_BIN_DATA_ADDR__MASK			0xffffffff
#define CP_SET_BIN_DATA_0_BIN_DATA_ADDR__SHIFT			0
static inline uint32_t CP_SET_BIN_DATA_0_BIN_DATA_ADDR(uint32_t val)
{
	return ((val) << CP_SET_BIN_DATA_0_BIN_DATA_ADDR__SHIFT) & CP_SET_BIN_DATA_0_BIN_DATA_ADDR__MASK;
}

#define REG_CP_SET_BIN_DATA_1					0x00000001
#define CP_SET_BIN_DATA_1_BIN_SIZE_ADDRESS__MASK		0xffffffff
#define CP_SET_BIN_DATA_1_BIN_SIZE_ADDRESS__SHIFT		0
static inline uint32_t CP_SET_BIN_DATA_1_BIN_SIZE_ADDRESS(uint32_t val)
{
	return ((val) << CP_SET_BIN_DATA_1_BIN_SIZE_ADDRESS__SHIFT) & CP_SET_BIN_DATA_1_BIN_SIZE_ADDRESS__MASK;
}


#endif /* ADRENO_PM4_XML */
