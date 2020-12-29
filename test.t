ssp 4
ldc 6
str 3
ldc 's'
ldc 'I'
ldc '6'
ldc 'f'
ldc 'O'
ldc 'o'
ldc 'b'
ldc 'i'
ldc 'F'
outc
outc
outc
outc
outc
outc
outc
outc
outc
mst
lod 3
cup 1 F1
out
ldc 0
str 0
stp
F1: ssp 5
lod 3
ldc 1
leq
fjp L1
lod 3
str 4
ujp L2
L1: mst
lod 3
ldc 1
sub
cup 1 F1
mst
lod 3
ldc 2
sub
cup 1 F1
add
str 4
L2: lod 4
str 0
retf
