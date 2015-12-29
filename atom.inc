;Define textcolours

green         = $00; 00 000000
yellow        = $40; 01 000000
blue          = $80; 10 000000
red           = $c0; 11 000000

.macro defblock nr,databyte
	.repeat nr
	  .byte databyte
	.endrep
.endmacro

