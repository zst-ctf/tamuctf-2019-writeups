# :)
Crypto

## Challenge 

Look at what I found!
	
	XUBdTFdScw5XCVRGTglJXEpMSFpOQE5AVVxJBRpLT10aYBpIVwlbCVZATl1WTBpaTkBOQFVcSQdH

Difficulty: easy

## Solution

### Part 1: Base64 decode

Upon base64 decoding it, we get some weird text 

	$ echo XUBdTFdScw5XCVRGTglJXEpMSFpOQE5AVVxJBRpLT10aYBpIVwlbCVZATl1WTBpaTkBOQFVcSQdH | base64 -D | xxd
	00000000: 5d40 5d4c 5752 730e 5709 5446 4e09 495c  ]@]LWRs.W.TFN.I\
	00000010: 4a4c 485a 4e40 4e40 555c 4905 1a4b 4f5d  JLHZN@N@U\I..KO]
	00000020: 1a60 1a48 5709 5b09 5640 4e5d 564c 1a5a  .`.HW.[.V@N]VL.Z
	00000030: 4e40 4e40 555c 4907 47                   N@N@U\I.G

### Part 2: XOR cipher

This took me some time to realise, but look at the first few characters

	]@]LW

There is a repetition of `]`. This corresponds to the standard flag format of `gigem` where `g` is repeated.

Hence, try an XOR cipher.

	>>> import base64

	>>> def xor_zip_bytes(bytearray1, bytearray2):
	...     final = b''
	...     for a, b in zip(bytearray1, bytearray2):
	...         final += bytes([a ^ b])
	...     return final

	>>> decoded = base64.b64decode('XUBdTFdScw5XCVRGTglJXEpMSFpOQE5AVVxJBRpLT10aYBpIVwlbCVZATl1WTBpaTkBOQFVcSQdH')

	>>> xor_zip_bytes(decoded, b'gigem')
	b':):):'

From here we realise that it consists of `:)` characters as the key. Let's make it a cyclic key and try again

	>>> from itertools import cycle
	>>> key = cycle(b':)')
	>>> xor_zip_bytes(decoded, key)
	b"gigem{I'm not superstitious, but I am a little stitious.}"

## Flag

	gigem{I'm not superstitious, but I am a little stitious.}
