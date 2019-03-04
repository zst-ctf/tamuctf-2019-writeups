# Holey Knapsack
Crypto

## Challenge 

	My knapsack has a hole in it

	Cipher text: 11b90d6311b90ff90ce610c4123b10c40ce60dfa123610610ce60d450d000ce61061106110c4098515340d4512361534098509270e5d09850e58123610c9

	Public key: {99, 1235, 865, 990, 5, 1443, 895, 1477}

	The flag is slightly off format.

	Difficulty: medium

## Solution

### Knapsack Cryptosystem

#### Merkle-Hellman Knapsack Cryptosystem

Knapsack Encryption (Merkle-Hellman Knapsack):
- https://asecuritysite.com/encryption/knapcode

Poking Holes in Knapsack Cryptosystems
- http://courses.cs.washington.edu/courses/csep590/06wi/finalprojects/Myers-Knapsack3.ppt

Cryptanalysis of a Knapsack Cryptosystem
- https://unbscholar.lib.unb.ca/islandora/object/unbscholar%3A7040/datastream/PDF/view

CTF writeups
- http://komang4130.blogspot.com/2017/07/meepwn-ctf-2017-nubcryptosystem-task.html
- http://gnoobz.com/plaid-ctf-2015-lazy-writeup.html
- https://github.com/ctfs/write-ups-2014/tree/master/asis-ctf-quals-2014/archaic


#### solving

The ciphertext should consist of multiple numbers. However, only one combined one is given.

The public key is 8 numbers long. Hence, the ciphertext is 8-bits long.

---

This is the sum of all elements in the public key.

	sum = 7009 = 0x1b61

I assume the hex numbers are concatted together. Hence, I decided to split up the ciphertext into chunks of 4 chars (ie. 2 hex-pairs). (***I did some trial and error to realise that 4 chars must be used.***)

	split = 4  # every 4 chars
	for i in range(0, len(c), split):
	    ct = int(c[i:i+split], 16)

After which, we can do LLL attack on each of the ciphertext chunks to get a solution.

	# create a large matrix of 0's (dimensions are public key length +1)
    M = Matrix(ZZ, matrix_size, matrix_size)

    # fill in the identity matrix
    for i in range(matrix_size):
        M[i, i] = 1

    # bottom right is encoded message
    M[nbit, nbit] = -c

    # right column is public keys
    for i in range(nbit):
        M[i, nbit] = publicKey[i]

    # lattice basis reduction
    result = M.LLL()


---

After doing LLL reduction, we realise there's a group of vectors.

We need to automatically choose it. Since the vectors will be the plaintext, simply choose the one with only 1s and 0s indicating the binary bits.

    # choose vector by only binary 1s and 0s
    condition = lambda x: x == 1 or x == 0
    good_vector = all(condition(item) for item in mylist)
    if not good_vector:
        continue

---

So running it all, we get a partial flag.

	$ sage test.sage
	('sum', 7009, '1b61')
	0x11b9 [1, 1, 1, 0, 0, 1, 1, 0, 0] 001100111 g
	0xd63 [1, 0, 0, 1, 0, 1, 1, 0, 0] 001101001 i
	0x11b9 [1, 1, 1, 0, 0, 1, 1, 0, 0] 001100111 g
	0xff9 no solution
	0xce6 [1, 0, 1, 0, 0, 1, 1, 0, 0] 001100101 e
	0x10c4 [1, 0, 1, 1, 0, 1, 1, 0, 0] 001101101 m
	0x123b no solution
	0x10c4 [1, 0, 1, 1, 0, 1, 1, 0, 0] 001101101 m
	0xce6 [1, 0, 1, 0, 0, 1, 1, 0, 0] 001100101 e
	0xdfa no solution
	0x1236 [1, 1, 0, 1, 0, 1, 1, 0, 0] 001101011 k
	0x1061 [0, 0, 1, 1, 0, 1, 1, 0, 0] 001101100 l
	0xce6 [1, 0, 1, 0, 0, 1, 1, 0, 0] 001100101 e
	0xd45 [1, 0, 1, 1, 0, 1, 0, 0, 0] 000101101 -
	0xd00 [0, 0, 0, 1, 0, 1, 1, 0, 0] 001101000 h
	0xce6 [1, 0, 1, 0, 0, 1, 1, 0, 0] 001100101 e
	0x1061 [0, 0, 1, 1, 0, 1, 1, 0, 0] 001101100 l
	0x1061 [0, 0, 1, 1, 0, 1, 1, 0, 0] 001101100 l
	0x10c4 [1, 0, 1, 1, 0, 1, 1, 0, 0] 001101101 m
	0x985 [1, 0, 0, 0, 0, 1, 1, 0, 0] 001100001 a
	0x1534 [0, 1, 1, 1, 0, 1, 1, 0, 0] 001101110 n
	0xd45 [1, 0, 1, 1, 0, 1, 0, 0, 0] 000101101 -
	0x1236 [1, 1, 0, 1, 0, 1, 1, 0, 0] 001101011 k
	0x1534 [0, 1, 1, 1, 0, 1, 1, 0, 0] 001101110 n
	0x985 [1, 0, 0, 0, 0, 1, 1, 0, 0] 001100001 a
	0x927 no solution
	0xe5d no solution
	0x985 [1, 0, 0, 0, 0, 1, 1, 0, 0] 001100001 a
	0xe58 [1, 1, 0, 0, 0, 1, 1, 0, 0] 001100011 c
	0x1236 [1, 1, 0, 1, 0, 1, 1, 0, 0] 001101011 k
	0x10c9 [1, 0, 1, 1, 1, 1, 1, 0, 0] 001111101 }
	gig?em?me?kle-hellman-kna??ack}

With the partial flag, it looks almost correct

	gig?em?me?kle-hellman-kna??ack}

So with some intelligent guessing, we get the real flag

	gigem{merkle-hellman-knapsack}

## Flag

	gigem{merkle-hellman-knapsack}
