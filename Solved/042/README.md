# 042
Reversing

## Challenge 

	Cheers for actual assembly!

	#medium

[reversing3.s](reversing3.s)

## Solution

Out of pure inspection, we see the flag here

	movb	$65, -16(%rbp)
	movb	$53, -15(%rbp)
	movb	$53, -14(%rbp)
	movb	$51, -13(%rbp)
	movb	$77, -12(%rbp)
	movb	$98, -11(%rbp)
	movb	$49, -10(%rbp)
	movb	$89, -9(%rbp)

Construct the flag

	>>> x = [65,53,53,51,77,98,49,89]

	>>> "gigem{%s}\n"   %   ''.join( list(map(chr, x)) )
	'gigem{A553Mb1Y}\n'

## Flag

	gigem{A553Mb1Y}
