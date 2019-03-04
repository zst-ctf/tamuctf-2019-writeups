#!/usr/bin/env python3
from itertools import cycle

def xor(a1, b1):
	encrypted = [ (a ^ b) for (a,b) in zip(a1, b1) ]
	return bytes(encrypted)

encrypted = bytes([0xae, 0x9e, 0xff, 0x9c, 0xab, 0xc7, 0xd3, 0x81, 0xe7, 0xee, 0xfb, 0x8a, 0x9d, 0xef, 0x8d, 0xae])
print('encrypted', encrypted)

key = bytes.fromhex('deadbeef')
print('key', key)

decrypted = xor(encrypted, cycle(key))
print('decrypted', decrypted)
