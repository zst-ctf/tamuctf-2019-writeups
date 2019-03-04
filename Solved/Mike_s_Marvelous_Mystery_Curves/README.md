# Mike's Marvelous Mystery Curves
Crypto

## Challenge 

Mike, the System Administrator, thought it would be a good idea to implement his own Elliptic Curve Diffie Hellman key exchange using unnamed curves to use across the network. We managed to capture network traffic of the key exchange along with an encrypted file transfer. See if you can read the contents of that file.

Note: The password to the AES192-CBC encrypted file is the shared key x and y coordinates from the key exchange concatenated together. (e.g. sharedKey = (12345,67890) password = "1234567890")

Difficulty: hard

Edit: 02/23/2019 14:33 Changed AES256-CBC to AES192-CBC

## Solution

### References

Theory and Examples:
- https://medium.com/coinmonks/the-wonderful-world-of-elliptic-curve-cryptography-b7784acdef50
- https://asecuritysite.com/encryption/ecdh
- http://mslc.ctf.su/wp/hack-lu-ctf-2011-wipe-out-the-klingons-400/
- https://github.com/hgarrereyn/Th3g3ntl3man-CTF-Writeups/blob/master/2017/picoCTF_2017/problems/cryptography/ECC2/ECC2.md

Certificate format:
- https://wiki.openssl.org/index.php/Command_Line_Elliptic_Curve_Operations

Additional References:
- https://en.wikipedia.org/wiki/Elliptic-curve_Diffie–Hellman
- https://www.semiwiki.com/forum/content/3966-ecdh-key-exchange-practical-magic.html
- https://jeremykun.com/2014/03/31/elliptic-curve-diffie-hellman/
- https://andrea.corbellini.name/2015/05/30/elliptic-curve-cryptography-ecdh-and-ecdsa/
- http://www-cs-students.stanford.edu/~tjw/jsbn/ecdh.html
- https://crypto.stackexchange.com/questions/33135/how-do-we-calculate-dhkey-using-as-public-key-and-bs-private-key


---

### WireShark extract files

From the PCAP, we see 2 certificates at frames 4 and 11

We also see a series of file transfers between frames 18 to 31.

There is also a series of file transfer after that.

Extract out the files using `Follow > TCP Stream`.

### Key Exchange Certificates

Read out the certificates

	cat 4_certificate.bin | head -2 | tail -1 | base64 -D
	cat 11_certificate.bin | head -2 | tail -1 | base64 -D

We see the Elliptic Curve Diffie Hellman (ECHD) parameters are common

	ASN1 OID: badPrime96v4
	CURVE: JustNo
	    Field Type: prime-field
	    Prime:
	        412220184797
	    A:   
	        10717230661382162362098424417014722231813
	    B:   
	        22043581253918959176184702399480186312
	    Generator:
	        56797798272
	        349018778637

But for each file, there is a different public key for Bob and Alice

	Bob Public-Key:
	    196393473219
	    35161195210

	Alice Public-Key:
	    61801292647
	    228288385004


---

### Solve ECHD private keys

From the above, we derive the following

	// Curve parameters (y² = x³ + ax + b)
	_prime = 412220184797
	_a = 10717230661382162362098424417014722231813
	_b = 22043581253918959176184702399480186312

	// Generator (Base Point)
	_Gx = 56797798272   (mod _prime)
	_Gy = 349018778637  (mod _prime)
	_G = (_Gx, _Gy)

	// Private Key (dA, dB)
	Priv_a = ?
	Priv_b = ?

	// Public Key (QA, QB)
	Pub_A = (61801292647, 228288385004)
	Pub_B = (196393473219, 35161195210)

	where, Pub_A = _G * Priv_a (mod _prime)
	where, Pub_B = _G * Priv_b (mod _prime)

	// Shared Key 
	Share_A = Pub_A * Priv_b = _G * Priv_a * Priv_b (mod _prime)
	Share_B = Pub_B * Priv_a = _G * Priv_a * Priv_b (mod _prime)

Since the prime is small, private keys can be easily solved using the **discrete log algorithm**.

I wrote a simple script in sage.

Solved for the private keys

	$ time sage solve.sage 
	('Private Key A:', 54628069049)
	('Private Key B:', 6895697291)
	('Shared Key:', (130222573707 : 242246159397 : 1))

	real	0m5.016s
	user	0m2.436s
	sys	0m1.146s

---

### Decrypt files

So we know from the challenge description that the passwords are concatted together.

	AES192-CBC
	password = "130222573707242246159397"

So we decrypt

	# decrypt
	openssl enc -aes-192-cbc -d -in encrypted.bin -out decrypted.bin -pass pass:130222573707242246159397
	openssl enc -aes-192-cbc -d -in encrypted.bin -out decrypted.bin -pass pass:130222573707242246159397 -nosalt 

Somehow it doesn't work at all in OpenSSL to decrypt with errors such as `bad magic number`

***Wasted so many days trying to figure out what is wrong***

After speaking to an admin, I should use PyCrypto to decrypt it. It works prefectly on first try with any IV used.

	$ python3 decrypt.py | grep gigem
	gigem{Forty-two_said_Deep_Thought}, with infinite majesty and calm.

I have a feeling it is due to OpenSSL verifying the decrypted text, thus throwing errors and preventing the decryption.

## Flag

	gigem{Forty-two_said_Deep_Thought}
