#!/usr/bin/env python3

from Crypto import Random
from Crypto.Cipher import AES
import sys
import time
import binascii
import base64

def xor_zip_bytes(bytearray1, bytearray2):
    final = b''
    for a, b in zip(bytearray1, bytearray2):
        final += bytes([a ^ b])
    return final

def pad(bytetext, length):
    pad_size = (length - len(bytetext))
    #pad_size = (self.bs - len(s) % self.bs)
    return bytetext + pad_size * bytes([pad_size])

def pad2(bytetext, length):
    bytetext += b'\x00' * (length - len(bytetext))
    return bytetext

def get_keystream(text, encoded_base64):
    ciphertext = base64.b64decode(encoded_base64)
    plaintext = pad(text.encode(), len(ciphertext))

    assert len(plaintext) == len(ciphertext)
    keystream = xor_zip_bytes(plaintext, ciphertext)

    print("=============================================")
    print("plaintext:", plaintext)
    print("ciphertext:", ciphertext)
    print("keystream:", keystream)
    print()

    return keystream

def decode_with_keystream(keystream, encoded_base64):
    ciphertext = base64.b64decode(encoded_base64)
    decode = xor_zip_bytes(keystream, ciphertext)
    print("ciphertext:", ciphertext)
    print("decoded:", decode)
    print()
    return decode


'''
def calculate_share_code(plaintext, keystream):
    plaintext = plaintext.encode() + b".txt"
    ciphertext = xor_zip_bytes(plaintext, keystream)
    share_code = base64.b64encode(ciphertext)

    print("Share code:", share_code)
    print()

    return share_code
'''

'''
def debug():
    send = "AAAAAAAAAAAAAAAAAAAAAAAAA"
    recv = "iKUkWi+QdHLy49jMpwUb2IilJFovkHRy8ozt9ZI="
    keystream = get_keystream(send, recv)

    send2 = "BBBBBBBBBBBBBBBBBBBBBBBBB" 
    recv2 = "i6YnWSyTd3Hx4NvPpAYY24umJ1ksk3dx8Yzt9ZI="
    keystream2 = get_keystream(send2, recv2)

    assert keystream == keystream2
    assert recv2 == calculate_share_code(send2, keystream2).decode()
'''

def main():
    encs = '''/Ks7iNV5tZaZT32Epav0CA==
0bGyNN1VKjWCxituvKDVvg==
4iLXaYY1As8N9+wW+PVQOg==
83jbJmmZc/RUXML8GcGuVg==
9+fXRGjlf3TvpwR6XiqcSw==
92fKIeYPq2HyqG8DSo2Mfw==
KLVDOWDtxnck6THwQuPfGg==
L2/wiXcz7QQyFdbuDe14+w==
MC9KVKLGfFmxvdr6qNuZpA==
MufXoG4oKY+tLj7TNMzMtQ==
RdGNIA97r2yYuQsdXjbQGA==
S+79/0xJH6oVAqvGSE+Vlw==
Tkb8E728rfsc+V1i5HtOzQ==
US5MJOeTx6L69iQT3Y8B9g==
WSThaqht6loKlvNDraoarw==
XpjdNQ+r0XfWy25TW5lyAg==
YiqMxpZQz+5dPf+qELowBw==
bIyEa1uO0qUPR+sBqjAJ8g==
gCe+M22NmuwF6cPVKGGoZQ==
h8zZvECdaFr730Mgo5EgYQ==
lwzGU75ZfX1C+vFQE1ahTQ==
mJoY/dqOlVLjsIzq/ZmGbg==
vCffRJyLzPpoDVYNvxEtoA==
wJNrzltAAb7rg/64niXZNg=='''.strip().splitlines()

    for enc in encs:
        keystream = get_keystream('exit', enc)
        for enc2 in encs:
            if enc2 == enc: continue
            xored = decode_with_keystream(keystream, enc2)



if __name__ == '__main__':
    main()
