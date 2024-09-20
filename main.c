#include <vdp1.h>

int main(void) {
	/* VRAM初期設定 */
	setup_vram_command_table();
	setup_vram_color_lookup_table();

	return 0;
}
