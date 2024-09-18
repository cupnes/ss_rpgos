#include <ss.h>
#include <common.h>
#include <vdp1.h>

#define VDP1_JP_JUMP_NEXT	0
#define VDP1_JP_JUMP_ASSIGN	1
#define VDP1_JP_SKIP_ASSIGN	5

#define VDP1_CMD_DRAWING_END	0x8000

struct vdp1_command_coordinates {
	unsigned short cmdctrl;
	unsigned short cmdlink;
	unsigned short cmdpmod;
	unsigned short cmdcolr;
	unsigned short cmdsrca;
	unsigned short cmdsize;
	unsigned short cmdxa;
	unsigned short cmdya;
	unsigned short cmdxb;
	unsigned short cmdyb;
	unsigned short cmdxc;
	unsigned short cmdyc;
	unsigned short cmdxd;
	unsigned short cmdyd;
	unsigned short cmdgrda;
	unsigned short dummy;
};

const struct vdp1_command_coordinates VDP1_COMMAND_SYSTEM_CLIPPING_COORDINATES = {
	0x0009,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x013f,
	0x00df,
	0x0000,
	0x0000,
	0x0000,
	0x0000
};

const struct vdp1_command_coordinates VDP1_COMMAND_USER_CLIPPING_COORDINATES = {
	0x0008,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x013f,
	0x00df,
	0x0000,
	0x0000,
	0x0000,
	0x0000
};

const struct vdp1_command_coordinates VDP1_COMMAND_LOCAL_COORDINATES = {
	0x000a,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	0x0000
};

const unsigned char SZ_VDP1_COMMAND_COORDINATES =
	sizeof(struct vdp1_command_coordinates);

/*
VDP1 RAM
- サイズ：4 Mbits = 512 KB = 524288 (0x0008 0000) bytes
- 領域：0x05C0 0000 - 0x05C7 FFFF
- メモリマップ：
  | 05C0 0000 - 05C0 7FFF ( 32 KB) | コマンドテーブル(CT)
  |                 -> 0000 - 005F | - 毎フレーム設定系
  |                 -> 0060 - 7FFF | - その他
  | 05C0 8000 - 05C7 EFFF (476 KB) | キャラクタパターンテーブル(CPT)
  |             -> 0 8000 - 7 EFFF | - その他
  | 05C7 F000 - 05C7 FFFF (  4 KB) | カラールックアップテーブル(CLT)&グーローシェーディングテーブル
*/
const unsigned int VRAM_CT_BASE = SS_VDP1_VRAM_ADDR;
const unsigned int VRAM_CT_OTHER_BASE = SS_VDP1_VRAM_ADDR + 0x60;
const unsigned int VRAM_CPT_BASE = SS_VDP1_VRAM_ADDR + 0x8000;
const unsigned int VRAM_CPT_OTHER_BASE = VRAM_CPT_BASE;
const unsigned short VRAM_CPT_OTHER_BASE_CMDSRCA = (VRAM_CPT_OTHER_BASE - SS_VDP1_VRAM_ADDR) / 8;
const unsigned int VRAM_CLT_BASE = SS_VDP1_VRAM_ADDR + 0x7f000;
/*描画コマンドのCMDCOLR設定用
  VDP1 RAM先頭(0x05C00000)からのオフセットを8で割った2バイトの値 */
const unsigned short VRAM_CLT_BASE_CMDCOLR = (VRAM_CLT_BASE - SS_VDP1_VRAM_ADDR) / 8;

/* コマンドテーブル設定 */
void setup_vram_command_table(void) {
	/* 0x05c00000 */
	unsigned short *com_adr = (unsigned short *)SS_VDP1_VRAM_ADDR;
	memcpy(com_adr, &VDP1_COMMAND_SYSTEM_CLIPPING_COORDINATES,
	       SZ_VDP1_COMMAND_COORDINATES);

	/* 0x05c00020 */
	/* com_adrはshort型のポインタなので1進めると2バイト進むため2で割る */
	com_adr += SZ_VDP1_COMMAND_COORDINATES / 2;
	memcpy(com_adr, &VDP1_COMMAND_USER_CLIPPING_COORDINATES,
	       SZ_VDP1_COMMAND_COORDINATES);

	/* 0x05c00040 */
	com_adr += SZ_VDP1_COMMAND_COORDINATES / 2;
	memcpy(com_adr, &VDP1_COMMAND_LOCAL_COORDINATES,
	       SZ_VDP1_COMMAND_COORDINATES);

	/* コマンドテーブルのその他の1件目に描画終了コマンドを配置 */
	com_adr = (unsigned short *)VRAM_CT_OTHER_BASE;
	*com_adr = VDP1_CMD_DRAWING_END;
}