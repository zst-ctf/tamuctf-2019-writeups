# Many Gig'ems to you
Web

## Challenge 

http://web7.tamuctf.com

## Solution


On index.html and cookies.html, we see many pictures. Looking at the HTML code, we realise there are some text in the ALT tags.

If we were to look at the website cookies, we see even more text.

	>> document.cookie
	"gigem_continue=cookies}; hax0r=flagflagflagflagflagflag; gigs=all_the_cookies; cookie=flagcookiegigemflagcookie"

---

We simply need to crack the code.

Now if we look carefully, we see some outstanding texts which I extracted below

	     index.html:  gigem{flag_in_
	   cookies.html:  gigem{continued == source_and_
	document.cookie:  gigem_continue=cookies}

Hence, I deduce the flag

	gigem{flag_in_source_and_cookies}

## Flag

	gigem{flag_in_source_and_cookies}
