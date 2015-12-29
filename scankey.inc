;------------------------------------------------
; Scankey X
; - X = scancode same as $FE71
; - Exit -> Y=255 = key pressed
;           Y=0   = key not pressed
;------------------------------------------------

scankey:
	txa
	cmp #$80 ; Scan CTRL
	bne sk10
	lda $b001
	and #$40
	bne sk4
	jmp sk13
sk10:
	cmp #$81 ; Scan REPT
	bne sk11
	lda $b002
	and #$40
	bne sk4
	jmp sk13

sk11:
	cmp #$82 ; Scan SHIFT
	bne sk12
	lda $b001
	and #$80
	bne sk4
	jmp sk13

sk12:
	ldx #0
sk1:
	cmp #10
	bcc sk5
	inx
	sec
	sbc #10
	jmp sk1
sk5:
	eor #$ff
	clc
	adc #10
	sta keyrow

	lda #1
	sta keycol

	lda $b000
	and #$f0
	ora keyrow
	sta $b000
sk3:
	cpx #0     ; Set keycol mask
	beq sk2
	dex	
	asl keycol
	jmp sk3
sk2:
	lda $b001  ; Read keycol
	and keycol
	bne sk4
sk13:
	ldy #255
	rts
sk4:
	ldy #0
	rts

keyrow:  .byte 0
keycol:  .byte 0

