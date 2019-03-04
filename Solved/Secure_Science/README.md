# Science
Secure Coding

## Challenge 

https://gitlab.tamuctf.com/root/science

	Now that you have broken the Jinja2 Template Injection challenge it's your turn to fix it!
	To solve this challenge you must first fork the challenge and then modify the files in this repository and attempt to fix the vulnerability that you found.
	Everytime you make a commit your files are tested on the backend system. The results can be found under CI/CD->Jobs and then the last test ran.
	If you pass all of the tests the flag will be printed at the bottom of the CI/CD display. Otherwise you will either get an error or statement saying what happened.

## Solution

This is in relation to the previous [Science](../Solved/Science) challenge.

We need to fix Flask injection. Simply use the built-in Flask templating...

- https://www.reddit.com/r/flask/comments/3vu7u4/injection_attacks_against_flask_blog/cxrgbzs
- https://nvisium.com/blog/2015/12/07/injecting-flask.html

Compare [before](views-before.py) and [after](views-after.py)

	Pushing: {'serviceHost': '172.17.0.3', 'userInfo': u'1891073034cf3fda112a0e73c846b243525e0e761245af1a3be47a9073f35c9e', 'chal': 'flask_server'}
	{"msg": "Service Check Succeeded After Attack\nflag: gigem{br0k3n_fl4sk_2d88bb862569}"}
	Job succeeded

## Flag

	gigem{br0k3n_fl4sk_2d88bb862569}
