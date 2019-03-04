from Crypto.Util.number import *
from Crypto.Cipher import AES

with open("encrypted.bin", "rb") as f:
    encrypted = f.read()

key = b"130222573707242246159397"

def decrypt():
    cipher = AES.new(key, mode=AES.MODE_CBC, IV='\x00'*16)
    return cipher.decrypt(encrypted)

print(decrypt().decode())
