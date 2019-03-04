#!/usr/bin/env python3
# export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:~/Downloads/z3-4.8.0.99339798ee98-x64-osx-10.11.6/bin
# export PYTHONPATH=~/Downloads/z3-4.8.0.99339798ee98-x64-osx-10.11.6/bin/python
from z3 import *
#from math import pi as PI
#from math import e as E
#from math import log as ln

key = IntVector("key", 29)
s = Solver()

############################################
### Setup

# Product key is ASCII 8-bit
for i in range(29):
    s.add(key[i] >= 0x00)
#    s.add(key[i] <= 0xFF)

############################################
### Reversing - Part 1

# check_01
s.add((key[0x5] == 0x2d))
s.add((key[0xb] == 0x2d))
s.add((key[0x11] == 0x2d))
s.add((key[0x17] == 0x2d))

# check_02
'''
s.add((key[0x1] <= 0x39))
s.add((key[0x4] <= 0x39))
s.add((key[0x6] <= 0x39))
s.add((key[0x9] <= 0x39))
s.add((key[0xf] <= 0x39))

s.add((key[0x12] <= 0x39))
s.add((key[0x16] <= 0x39))
s.add((key[0x1b] <= 0x39))
s.add((key[0x1c] <= 0x39))
'''

# check_02, fixed it to within digits
s.add((key[0x1] <= 0x39), (key[0x1] >= 0x30))
s.add((key[0x4] <= 0x39), (key[0x4] >= 0x30))
s.add((key[0x6] <= 0x39), (key[0x6] >= 0x30))
s.add((key[0x9] <= 0x39), (key[0x9] >= 0x30))
s.add((key[0xf] <= 0x39), (key[0xf] >= 0x30))

s.add((key[0x12] <= 0x39), (key[0x12] >= 0x30))
s.add((key[0x16] <= 0x39), (key[0x16] >= 0x30))
s.add((key[0x1b] <= 0x39), (key[0x1b] >= 0x30))
s.add((key[0x1c] <= 0x39), (key[0x1c] >= 0x30))


# check_0B
s.add((key[0x14] == 0x42))
s.add((key[0x15] == 0x42))

# check_0F
s.add((key[0] == 0x4d))

############################################
### Reversing - Part 2

# check_03
s.add((key[4] - 0x30) == 1 + (key[1] - 0x30) + (key[1] - 0x30))
s.add(key[4] > 0x37)
s.add(key[9] == (key[4] - key[1]) + 0x32)

############################################
### Reversing - Part 3

# check_04
s.add((key[0x1b] + key[0x1c]) % 13 == 8)

# check_05
s.add((key[0x1b] + key[0x16]) % 22 == 0x12)
    
# check_06
s.add((key[0x12] + key[0x16]) % 11 == 5)

# check_07
s.add((key[0x12] + key[0x1c] + key[0x16]) % 26 == 4)

# check_08
s.add((key[1] + key[6]*key[4]) % 41 == 5)

# check_0C
s.add((key[0x6] + key[0x9] * key[0xf]) % 10 == 1)


############################################
### Reversing - Part 4

# check_09
rdx = key[0xf]
rax = key[0x1c]
# s.add(((rdx - rax - rax) & 0x3) == 0x1)
s.add(((rdx - rax - rax) % 4) == 0x1)

'''
# check_0A
rdx = key[0x4]
rax = key[0x16]
# s.add(((rax + rdx + rax) & 0x3) == 0x3)
s.add(((rax + rdx + rax) % 4) == 0x3)

#check_0D
rdx = key[0x4] + key[0xf]
rax = key[0x1b]
# s.add(((rax + rax + rdx - 36) & 0xf) == 0x8)
s.add(((rax + rax + rdx - 36) % 16) == 0x8)

# check_0E
rdx = key[0x1c]
rax = key[0x9]
# s.add(((rdx - rax - rax) & 0x1) == 0x1)
s.add(((rdx - rax - rax) % 2) == 0x1)
'''

if s.check() != sat:
    print("No solution")
    quit()
else:
    m = s.model()

    prodkey = [0] * 29
    for name in m:
        value = m[name]
        index = int(str(name).split('__')[1])
        prodkey[index] = int(str(value))
        print(f"{name} at {hex(index)} = {value}")


    prodkey = ''.join(list(map(lambda x: chr(x) if x else 'x', prodkey)))
    print('prodkey =', prodkey)
    print('prodkey (hex) =', prodkey.encode().hex())
