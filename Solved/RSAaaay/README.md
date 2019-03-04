# RSAaaay
Crypto

## Challenge 

Hey, you're a hacker, right? I think I am too, look at what I made!

	(2531257, 43)

	My super secret message: 906851 991083 1780304 2380434 438490 356019 921472 822283 817856 556932 2102538 2501908 2211404 991083 1562919 38268

Problem is, I don't remember how to decrypt it... could you help me out?

Difficulty: easy

## Solution

I'm guessing public key (n, e) = (2531257, 43)

Using factordb.com

	2531257 = 509 * 4973

Hence we have these

	p = 509
	q = 4973
	e = 43

Now using [some generic RSA decryption code](https://crypto.stackexchange.com/a/19530), we can solve for each of the ciphertext separately

This yields us the following.

	pt: 103
	pt: 105103
	pt: 101109
	pt: 12383
	pt: 97118
	pt: 97103
	pt: 10195
	pt: 83105
	pt: 12095
	pt: 70108
	pt: 121105
	pt: 110103
	pt: 9584
	pt: 105103
	pt: 101114
	pt: 115125

Notice that it looks like decimal of the ASCII chars joined together. Split them up



	>>> x = [103,105,103,101,109,123,83,97,118,97,103,101,95,83,105,120,95,70,108,121,105,110,103,95,84,105,103,101,114,115,125]
	
	>>> list(map(lambda a: chr(a), x))
	['g', 'i', 'g', 'e', 'm', '{', 'S', 'a', 'v', 'a', 'g', 'e', '_', 'S', 'i', 'x', '_', 'F', 'l', 'y', 'i', 'n', 'g', '_', 'T', 'i', 'g', 'e', 'r', 's', '}']

	>>> ''.join( list(map(lambda a: chr(a), x)) )
	'gigem{Savage_Six_Flying_Tigers}'



## Flag

	gigem{Savage_Six_Flying_Tigers}
