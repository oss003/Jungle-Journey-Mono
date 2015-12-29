;======================================================================
;FONT ROUTINES:
;======================================================================
;PUTSTRING
; - col,x,y,string,0
; - col,x,y,string,0
; - $ff
;
;PUTCHAR x,y,a
;======================================================================
XPOS     = $90
YPOS     = $91
COLOR    = $92
COLORTMP = $98

PUTSTRING:
    stx $e8
    sty $e9


    ldy #0
P_S_0:
    lda ($e8),y    ; Check end of printing
    cmp #$ff
    beq P_S_4

P_S_1:
    sta XPOS       ; Save x,y,attribute
    jsr setcolor
    jsr PTR_INC
    lda ($e8),y
    sta YPOS

P_S_2:
    jsr PTR_INC    ; Print character until 0
    lda ($e8),y
    beq P_S_5
    jsr PRINTCHAR
    inc XPOS
    jmp P_S_2
P_S_5:
    jsr PTR_INC
    jmp P_S_0

P_S_4:
    rts            ; Return to program

PTR_INC:           ; Increment textpointer
    inc $e8
    bne PTR_1
    inc $e9
PTR_1:
    rts

setcolor:
    sta COLORTMP
    lda XPOS
    and #31
    sta XPOS

    ldx #4
nshift:
    lda COLORTMP
    asl a
    rol COLOR
    asl a
    rol COLOR
    dex
    bne nshift
    rts

;----------------------------------------------------------------------
SCR      = $93
CHR      = $95
CHR1     = $9A
TMP_Y    = $97
TMP_A    = $98
TMP_DAT  = $99

PUTCHAR:
    stx XPOS
    sty YPOS

PRINTCHAR:
    sec
	sbc #32
	sta TMP_A
    sta CHR        ; Calculate characterspritedata address
    lda #0         ; = A * 8 + charsprite data address
    sta CHR+1
    asl CHR
    rol CHR+1
    asl CHR
    rol CHR+1
    asl CHR
    rol CHR+1
    lda CHR
    clc
    adc #<font
    sta CHR
	sta CHR1
    lda CHR+1
    adc #>font
    sta CHR+1
	clc
	adc #4
	sta CHR1+1
    
    lda XPOS       ; Calculate screenaddress
;-*-
	asl a
;-*-
    sta SCR
    lda YPOS
    clc
    adc #$80
    sta SCR+1
 
    sty TMP_Y
    ldx #0
    ldy #0         ; Put character on screen
P_C_1:

    lda (CHR),y
;---
	eor #$ff
	and #$aa
	sta TMP_DAT
	lda (CHR),y
	and COLOR
	ora TMP_DAT
	sta (SCR),y
;---
;    and COLOR
;    sta (SCR),y

    inc CHR
    bne P_C_2
    inc CHR+1
P_C_2:

;-*-
    lda (CHR1),y
	pha
    iny
;---
	eor #$ff
	and #$aa
	sta TMP_DAT
	pla
	and COLOR
	ora TMP_DAT
	sta (SCR),y
	dey
;---
;    and COLOR
;    sta (SCR),y

    inc CHR1
    bne P_C_3
    inc CHR1+1
P_C_3:
;-*-

    lda SCR
    clc
    adc #$20
    sta SCR
    lda SCR+1
    adc #0
    sta SCR+1
    inx
    cpx #8
    bne P_C_1

    ldy TMP_Y
    lda TMP_A
    rts
 
INV_CURSOR:
    stx SCR
    tya
    clc
    adc #$80
    sta SCR+1
 
    ldy #0         ; Put character on screen
IC1:
    lda (SCR),y
    eor #$ff
    sta (SCR),y
    tya
    clc
    adc #$20
    tay
    bne IC1
    rts    
