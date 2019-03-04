# Login App2
Secure Coding

## Challenge 

https://gitlab.tamuctf.com/root/loginapp

Now that you have broken the NoSQL Injection challenge it's your turn to fix it!
To solve this challenge you must first fork the challenge and then modify the files in this repository and attempt to fix the vulnerability that you found.
Everytime you make a commit your files are tested on the backend system. The results can be found under CI/CD->Jobs and then the last test ran.
If you pass all of the tests the flag will be printed at the bottom of the CI/CD display. Otherwise you will either get an error or statement saying what happened.

## Solution

Reference:
- http://scottksmith.com/blog/2015/06/08/secure-node-apps-against-owasp-top-10-injection/

> The exploit occurs because of the couple things. 
> First, we are allowing JSON data to be posted to our application.
> Second, we are not specifying the query selectors to use

In our case, this is the cause of the vulnerability
	
    var query = {
        username: req.body.username,
        password: req.body.password
    }
    // passed directly to `db.findOne()`
    // without query selector

> The solution to this exploit is simple. You need to explicity set the query selector.

    var query = {
        username: { $in: [req.body.username] },
        password: { $in: [req.body.password] }
    }
    // explicity set query selector here

Push the changes to Git and we pass the test

	DB initialized - connected to: 
	Up and running on port 4000
	172.17.0.3
	Pushing: {'serviceHost': '172.17.0.3', 'userInfo': u'4e138e4c9a748e4ebf5282b4f0f0bf05d9e081f319a85c7a7990dc76875363ce', 'chal': 'nosql_server'}
	{"msg": "Service Check Succeeded After Attack\nflag: gigem{3y3_SQL_n0w_6b95d3035a3755a}"}

## Flag

	gigem{3y3_SQL_n0w_6b95d3035a3755a}
