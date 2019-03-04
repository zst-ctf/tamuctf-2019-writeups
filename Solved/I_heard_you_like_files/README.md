# I heard you like files
Misc

## Challenge 

Bender B. Rodriguez was caught with a flash drive with only a single file on it. We think it may contain valuable information. His area of research is PDF files, so it's strange that this file is a PNG.

Difficulty: easy-medium

## Solution

### Part (1) 
Use foremost to extract the hidden files.

	# foremost art.png 

We see a PDF and a ZIP

### Part (2)

We notice that the ZIP file is actually a Word Doc.

	$ file foremost-00006700.zip
	foremost-00006700.zip: Microsoft Word 2007+

Opening the word doc, there is a photo, save it out.

### Part (3)

And when we do a strings, there is a base64 at the end of it

	$ strings image1.png | tail -1 | base64 --decode
	flag{P0lYt@r_D0_y0u_G3t_It_N0w?}

## Flag

	flag{P0lYt@r_D0_y0u_G3t_It_N0w?}
