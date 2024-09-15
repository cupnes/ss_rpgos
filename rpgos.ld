OUTPUT_FORMAT("binary");

MEMORY
{
	ram(wx)      : ORIGIN = 0x06004000, LENGTH = 1008k
}

SECTIONS
{
	.body : {
		*(.text)

		*(.rodata)

		*(.data)

		/* bssセクションが0クリアされている事を期待しないように
		 * プログラムを作ること。 */
		*(.bss)

		*(.eh_frame)
	} > ram
}
