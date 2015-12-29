;----------------------------------------------
;JUNGLE JOURNEY
; Original version for the BBC by David Boddie
; Atom conversion by Kees van Oss 2012
;----------------------------------------------
	.DEFINE asm_code $2b00
	.DEFINE header   1		; Header Wouter Ras emulator
	.DEFINE filenaam "JUNGLE"

.org asm_code-22*header

.IF header
;********************************************************************
; ATM Header for Atom emulator Wouter Ras

name_start:
	.byte filenaam			; Filename
name_end:
	.repeat 16-name_end+name_start	; Fill with 0 till 16 chars
	  .byte $0
	.endrep

	.word asm_code			; 2 bytes startaddress
	.word exec			; 2 bytes linkaddress
	.word eind_asm-start_asm	; 2 bytes filelength

;********************************************************************
.ENDIF
;complete	= $500

exec:
start_asm:
	.include "atom.inc"
	.include "mapcode.oph"
	.include "scankey.inc"
	.include "tapecode.oph"
	.include "sprites.inc"
	.include "font.inc"
	.include "joystick.inc"
	.include "sound.inc"
	.include "vars.inc" 
	.include "fontdat.inc"
	.include "chars.inc"
	.include "title.inc"
	.include "complete.inc"
eind_asm: