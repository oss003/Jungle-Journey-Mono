L0ee0:		defblock 16,0
L0ef0:		defblock 16,0
L5180:		defblock 8*12,0	; High scores
		defblock 32,0
L5280:		defblock 128,0	; Character table
L5200:		defblock 121,0	; Objects/treasure table
		defblock 7,0
L5300:		defblock 256,0	; Plot buffer
		defblock $360,0
L5760:		defblock 8,0	; Note data
		defblock 22,0
L577e:		.byte 0		; Joystick
L577f:		.byte 0		; Weapon counter
L5780:		.byte 0		; Item/player flags
L5781:		.byte 0		; Weapon/enemy limit
L5782:		.byte 0,0	; Current room (i,j)
L5784:		.byte 0		; Lives (strength)
L5785:		.byte 0		; Delay counter
L5786:		.byte 0,0,0	; Score
L5789:		.byte 0		; Projectile type
L578a:		.byte 0		; Level
L578b:		.byte 0,0	; Palette workspace
L578d:		.byte 0		; Projectile counter
L578e:		.byte 0		; Motion counter
L578f:		.byte 0		; Enemy generation counter
		defblock 12,0
L579c:		defblock 100,0	; Room data
L579d:		.byte 0

