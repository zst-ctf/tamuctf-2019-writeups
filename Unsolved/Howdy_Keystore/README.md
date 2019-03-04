# Howdy Keystore
Android

## Challenge 

One of your senior design team members decided to drop out of the university at the last minute to pursue a life of gigging. Before leaving they never gave the team the password to the keystore file for the Android app y'all were making. Can you recover the password? You seem to recall that they were a good Aggie despite dropping out.

The flag is in gigem{password} format.

The password contains Uppercase, lowercase, and numbers only.

Difficulty: medium

2/23 6:24 pm CST added hint to description

[howdyapp.keystore](howdyapp.keystore)

## Hint
https://en.wikipedia.org/wiki/Glossary_of_Texas_A%26M_University_terms

## Solution

https://maxcamillo.github.io/android-keystore-password-recover/

- Smart Wordlist Attack

Extract all words into a list (terms.txt)

Then I need to convert it into a dictionary list

	$ cat terms.txt 
		| tr '[:upper:]' '[:lower:]' # Convert all to lowercase
		| tr ' ' '\n'                # separate words into newlines
		| tr -cd '[:alpha:]\n'       # remove all non-alphabet and non-newlines
		| sort | uniq                # sort and remove duplicates
		| grep .                     # get nonn-empty lines
		> dictionary.txt

try

	$ java -jar Android_Keystore_Password_Recover_1.07.jar -m 3 -k howdyapp.keystore -d dictionary.txt

	Number of keys in keystore: 1
	Found alias: android
	Creation Date: Sat Dec 22 01:04:29 SRET 2018

	Starting smart wordlist attack on key!!
	Trying variations with first letter capitalized

	Firing up 4 threads



## Flag

	??