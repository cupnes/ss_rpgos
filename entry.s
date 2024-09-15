	.text

	# NMI以外の全ての割り込みをマスクする
	# 割り込みコントローラで選択された割り込みの優先レベルとCPUのステータス
	# レジスタ（SR）の割り込みマスクビット（I3〜I0[*1]）とが比較され、I3〜I0
	# ビットに設定されているレベルと同じか低い優先レベルの割り込みが保留され
	# る仕組みなので、I3〜I0ビットを全て1にし、全ての割り込みが保留されるよ
	# うにしている。
	# [*1] b0が右端で、b4〜b7
	stc	sr, r0
	or	#0xf0, r0
	ldc	r0, sr

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
