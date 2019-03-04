# 1337 Secur1ty
Web

## Challenge 

http://web6.tamuctf.com

Difficulty: hard

## Solution

QR code

	$ zbarimg chart.png 
	QR-Code:otpauth://totp/TAMU_CTF?secret=PK4QSNRXWUVZKUUE


I was still logged in with the cookies.

	document.cookie
	"userid=346; secret=Y3TAHXPZSC7O73UC"

## Flag

	??
