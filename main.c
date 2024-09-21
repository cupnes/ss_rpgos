#include <vdp1.h>
#include <vdp2.h>

int main(void) {
	/* VRAM初期設定 */
	setup_vram_command_table();
	setup_vram_color_lookup_table();

	/* VDP2/1の初期化 */
	vdp2_init();
	vdp1_init();

	return 0;
}
