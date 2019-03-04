# Secrets
Android

## Challenge 

Can you find my secrets?

[howdyapp.apk](howdyapp.apk)

## Solution

First let's decompile the APK

	$ apktool d howdyapp.apk 
	$ dex2jar howdyapp.apk 

Now, using JD-GUI, we notice nothing special in the app code.

It simply provides a button to increment the count.

	public class MainActivity extends AppCompatActivity
	{
	  protected void onCreate(final Bundle paramBundle)
	  {
	    super.onCreate(paramBundle);
	    setContentView(2131296282);
	    paramBundle = (TextView)findViewById(2131165214);
	    ((ImageButton)findViewById(2131165206)).setOnClickListener(new View.OnClickListener()
	    {
	      public void onClick(View paramAnonymousView)
	      {
	        int i = Integer.valueOf(paramBundle.getText().toString()).intValue();
	        paramBundle.setText(String.valueOf(i + 1));
	      }
	    });
	  }
	}

---

So I started looking into the resource files.

In res/values/strings.xml we see this...

    <string name="flag">Z2lnZW17aW5maW5pdGVfZ2lnZW1zfQ==</string>

Got the flag from the base64 string

	$ echo 'Z2lnZW17aW5maW5pdGVfZ2lnZW1zfQ==' | base64 -D
	gigem{infinite_gigems}

## Flag

	gigem{infinite_gigems}
