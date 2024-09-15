	.text

	# スタックポインタ（R15）の初期化
	# （0x06004000を設定している。）
	mov	#0x06, r15
	shll8	r15
	mov	#0x00, r0
	and	#0xff, r0
	or	r0, r15
	shll8	r15
	mov	#0x40, r0
	and	#0xff, r0
	or	r0, r15
	shll8	r15
	mov	#0x00, r0
	and	#0xff, r0
	or	r0, r15

infinite_loop:
	sleep
	bra	infinite_loop
	nop
