;---------------------------------------------------
; SOUND A,X,Y, produce tone
;
; A = Duration (1-255) * 0,005 usec
; X = Pitch (9-19)
; Y = Octave (0-7)
;---------------------------------------------------

dur_val   = $f0
pit_val   = $f1
oct_val   = $f2

sound:
	sta dur_val	; 4
	stx pit_val	; 4
	sty oct_val	; 4

	lda #<5000	; 2, Set Timer 2=0,005 sec
	sta $b808	; 4
	lda #>5000	; 2
	sta $b809	; 4

	cpx #0
	bne loop3
	jmp pauseloop
loop3:
	  jsr toggle	     ;22 , t3=t2+22+3

	  ldy oct_val        ; 4 , t2=Y*(t1+4)+4
loop2:	    ldx pit_val      ; 4 , t1=X*32+4
loop1:	      lda $b80d       	; 4, Read IFR
	      and #$20     	; 2, Mask T2
	      bne chk_timer  	; 2 If T2=0, jump
	      jsr wait       	; 6+18 Else wait
loop5:	      dex            	; 2
	    bne loop1        	; 2
	    dey              ; 2
	  bne loop2          ; 2

	jmp loop3            ; 3

end_sound:
	rts             

;--------------------------------------
; Pause 
;--------------------------------------
pauseloop:
	ldy dur_val
loop10:
	lda #<5000
	sta $b808
	lda #>5000
	sta $b809
loop11:
	lda $b80d
	and #$20
	beq loop11

	lda $b808
	dey
	bne loop10
	rts

;--------------------------------------
; Toggle speaker (16 usec)
;--------------------------------------
toggle:
	lda $b002      ; 4
	eor #4         ; 2
	sta $b002      ; 4
	rts            ; 6

;--------------------------------------
; Check if time is over (24 usec)
;--------------------------------------
chk_timer:
	lda $b808      ; 4
	dec dur_val    ; 3
	beq end_sound  ; 2
settimer:
	lda #<5000     ; 2
	sta $b808      ; 4
	lda #>5000     ; 2
	sta $b809      ; 4
	jmp loop5      ; 3

;--------------------------------------
; Wait routine 24-6=18 usec
;--------------------------------------
wait:
	nop            ; 2
	nop            ; 2
	nop            ; 2
	nop            ; 2
	nop            ; 2
	nop            ; 2
	rts            ; 6

