
start:
abs.s $f0, $f0      # 46000005 / 010001 10000 ..... ..... ..... 000101
add $v0, $v0, $v0   # 00000020 / 000000 ..... ..... ..... ..... 100000
add.s $f0, $f0, $f0 # 46000000 / 010001 10000 ..... ..... ..... 000000
addi $v0, 0         # 20000000 / 001000 ..... ..... ..... ..... ......
addiu $v0, 0        # 24000000 / 001001 ..... ..... ..... ..... ......
addu $v0, $v0, $v0  # 00000021 / 000000 ..... ..... ..... ..... 100001
and $v0, $v0, $v0   # 00000024 / 000000 ..... ..... ..... ..... 100100
andi $v0, 0         # 30000000 / 001100 ..... ..... ..... ..... ......
bc1f start          # 45000000 / 010001 01000 00000 ..... ..... ......
bc1fl start         # 45020000 / 010001 01000 00010 ..... ..... ......
bc1t start          # 45010000 / 010001 01000 00001 ..... ..... ......
bc1tl start         # 45030000 / 010001 01000 00011 ..... ..... ......
