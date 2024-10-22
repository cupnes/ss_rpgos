#include <vdp2.h>

#define VDP2_TVMD	*(unsigned short *)0x25f80000
#define VDP2_BGON	*(unsigned short *)0x25f80020
#define VDP2_PNCN0	*(unsigned short *)0x25f80030
#define VDP2_PLSZ	*(unsigned short *)0x25f8003a
#define VDP2_MPOFN	*(unsigned short *)0x25f8003c
#define VDP2_MPABN0	*(unsigned short *)0x25f80040
#define VDP2_MPCDN0	*(unsigned short *)0x25f80042
#define VDP2_PRISA	*(unsigned short *)0x25f800f0

/* VDP2の初期化 */
void vdp2_init(void) {
	/* VDP2のシステムレジスタ設定 */

	/* TVMD
	   - DISP(b15) = 1
	   - BDCLMD(b8) = 1 (Border Color Mode = Back screen)
	   - LSMD(b7-b6) = 0b00 (Interlace Mode = Non-Interlace)
	   - VRESO(b5-b4) = 0b00 (Vertical resolution = 224)
	   - HRESO(b2-b0) = 0b010 (Horizontal resolution = 640) */
	VDP2_TVMD = 0x8102;

	/* BGON
	   - Transparent enable = all enable
	   - On = all off */
	VDP2_BGON = 0x0000;

	/* PNCN0 */
	VDP2_PNCN0 = 0x4123;

	/* PLSZ */
	VDP2_PLSZ = 0x1234;

	/* MPABN0 */
	VDP2_MPABN0 = 0x2b1a;

	/* MPCDN0 */
	VDP2_MPCDN0 = 0x1d3c;

	/* MPOFN */
	VDP2_MPOFN = 0x1234;

	/* PRISA
	   - Sprite 0 priority number = 6
	   - Sprite 1 priority number = 0 */
	VDP2_PRISA = 0x0006;
}
