# Snakes over cheese
Reversing

## Challenge 

What kind of file is this?

[reversing2.pyc](reversing2.pyc)


## Solution

We can use [uncompyle6](https://pypi.org/project/uncompyle6/) to reverse the pyc file into Python code.


	$ uncompyle6 reversing2.pyc 

	# uncompyle6 version 3.2.5
	# Python bytecode 2.7 (62211)
	# Decompiled from: Python 2.7.15 (default, Jul 28 2018, 11:29:29) 
	# [GCC 8.1.0]
	# Embedded file name: reversing2.py
	# Compiled at: 2018-10-07 19:28:58
	from datetime import datetime
	Fqaa = [102, 108, 97, 103, 123, 100, 101, 99, 111, 109, 112, 105, 108, 101, 125]
	XidT = [83, 117, 112, 101, 114, 83, 101, 99, 114, 101, 116, 75, 101, 121]

	def main():
	    print 'Clock.exe'
	    input = raw_input('>: ').strip()
	    kUIl = ''
	    for i in XidT:
	        kUIl += chr(i)

	    if input == kUIl:
	        alYe = ''
	        for i in Fqaa:
	            alYe += chr(i)

	        print alYe
	    else:
	        print datetime.now()


	if __name__ == '__main__':
	    main()
	# okay decompiling reversing2.pyc

We can read the strings

	>>> Fqaa = [102, 108, 97, 103, 123, 100, 101, 99, 111, 109, 112, 105, 108, 101, 125]
	>>> XidT = [83, 117, 112, 101, 114, 83, 101, 99, 114, 101, 116, 75, 101, 121]

	>>> ''.join( list(map(chr, Fqaa)) )
	'flag{decompile}'

	>>> ''.join( list(map(chr, XidT)) )
	'SuperSecretKey'

## Flag

	flag{decompile}
