# Robots Rule
Web

## Challenge 

http://web5.tamuctf.com

Difficulty: easy

## Solution

As name implies, visit robots.txt page

	$ curl http://web5.tamuctf.com/robots.txt
	User-agent: *

	WHAT IS UP, MY FELLOW HUMAN!
	HAVE YOU RECEIVED SECRET INFORMATION ON THE DASTARDLY GOOGLE ROBOTS?!
	YOU CAN TELL ME, A FELLOW NOT-A-ROBOT!~ $ 

It asks for Google Robot, so spoof the useragent

	$ curl http://web5.tamuctf.com/robots.txt -A 'Googlebot-Image/1.0'
	User-agent: *

	THE HUMANS SUSPECT NOTHING!
	HERE IS THE SECRET INFORMATION: gigem{be3p-bOop_rob0tz_4-lyfe}
	LONG LIVE THE GOOGLEBOTS!

## Flag

	gigem{be3p-bOop_rob0tz_4-lyfe}
