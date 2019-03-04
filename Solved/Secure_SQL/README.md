# SQL
Secure Coding

## Challenge 

https://gitlab.tamuctf.com/root/sql

	Now that you have broken the SQL Injection challenge it's your turn to fix it!
	To solve this challenge you must first fork the challenge and then modify the files in this repository and attempt to fix the vulnerability that you found.
	Everytime you make a commit your files are tested on the backend system. The results can be found under CI/CD->Jobs and then the last test ran.
	If you pass all of the tests the flag will be printed at the bottom of the CI/CD display. Otherwise you will either get an error or statement saying what happened.

## Solution

Fix SQLi
- https://www.acunetix.com/websitesecurity/sql-injection/

Original PHP code

    $user = $_POST['username'];
    $pass = $_POST['password'];

Wrap with `mysql_real_escape_string`

    $user = mysql_real_escape_string($_POST['username']);
    $pass = mysql_real_escape_string($_POST['password']);

However we get a fail

	Service Check Failed

---

Hmm... We are using mysqli so modify it to the correct format

http://php.net/manual/en/mysqli.real-escape-string.php

    $user = $conn->real_escape_string($_POST['username']);
    $pass = $conn->real_escape_string($_POST['password']);


## Flag

	


	u'50b1a2b2c63d9fb1d3dbd1bc8d218008ae3b251e850521c7c8f1b6a32d5b8824', 'chal': 'SQL'}
	Service Check Succeeded After Attack
	flag: gigem{the_best_damn_sql_anywhere}
	