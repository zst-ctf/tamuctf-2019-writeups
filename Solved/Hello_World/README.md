# Hello World
Misc

## Challenge 

My first program!

Difficulty: medium

hello_world.cpp

## Solution

### [Whitespace program](https://en.wikipedia.org/wiki/Whitespace_(programming_language)) 

Online interpretors
- https://vii5ard.github.io/whitespace/
- https://tio.run/#whitespace

It outputs the following

	Well sweet golly gee, that sure is a lot of whitespace!

Nothing much until we realise that there's some hidden characters

These are all the push-ed digits extracted out. It is clearly longer than the output text

	103,105,103,101,109,123,48,104,95,109,121,95,119,104,52,116,95,115,112,52,99,49,
	110,103,95,121,48,117,95,104,52,118,51,125,33,101,99,97,112,115,101,116,105,104,
	119,32,102,111,32,116,111,108,32,97,32,115,105,32,101,114,117,115,32,116,97,104,
	116,32,44,101,101,103,32,121,108,108,111,103,32,116,101,101,119,115,32,108,108,101,87

Consolidate it. And indeed we found that some chars were not printed

	>>> x = [103,105,103,101,109,123,48,104,95,109,121,95,119,104,52,116,95,115,112,52,99,49,110,103,95,121,48,117,95,104,52,118,51,125,33,101,99,97,112,115,101,116,105,104,119,32,102,111,32,116,111,108,32,97,32,115,105,32,101,114,117,115,32,116,97,104,116,32,44,101,101,103,32,121,108,108,111,103,32,116,101,101,119,115,32,108,108,101,87]

	>>> ''.join(list(map(chr, x)))
	'gigem{0h_my_wh4t_sp4c1ng_y0u_h4v3}!ecapsetihw fo tol a si erus taht ,eeg yllog teews lleW'

## Flag

	gigem{0h_my_wh4t_sp4c1ng_y0u_h4v3}
