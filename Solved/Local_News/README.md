# Local News
Android

## Challenge 

Be sure to check your local news broadcast for the latest updates!

Difficulty: medium-hard

## Solution

### Understand the source code

Decompile APK package

    dex2jar app.apk 
    apktool d app.apk 


MainActivity.class

    package com.tamu.ctf.hidden;

    import android.content.BroadcastReceiver;
    import android.content.Context;
    import android.content.Intent;
    import android.content.IntentFilter;
    import android.os.Bundle;
    import android.support.v4.content.LocalBroadcastManager;
    import android.support.v7.app.AppCompatActivity;
    import android.util.Log;
    import io.michaelrocks.paranoid.Deobfuscator.app.Debug;

    public class MainActivity extends AppCompatActivity {
      protected void onCreate(Bundle paramBundle) {
        super.onCreate(paramBundle);
        setContentView(2131296282);
        paramBundle = new BroadcastReceiver() {
          public void onReceive(Context paramAnonymousContext, Intent paramAnonymousIntent) {
            Log.d(MainActivity.this.getString(2131427360), Deobfuscator.app.Debug.getString(0));
          }
        };
        IntentFilter localIntentFilter = new IntentFilter();
        localIntentFilter.addAction(getString(2131427361));
        LocalBroadcastManager.getInstance(this).registerReceiver(paramBundle, localIntentFilter);
      }
    }

We know from the constants inside R.class that these resources are used.

    public static final int activity_main = 2131296282;
    public static final int flag = 2131427360;
    public static final int hidden_action = 2131427361;

    // <string name="flag">Flag:</string>
    // <string name="hidden_action">com.tamu.ctf.hidden.START</string>

### Working operation

So now how the app works is quite simple

1. Register a (Local) BroadcastReceiver of the action `com.tamu.ctf.hidden.START`
2. Deobfuscates the flag using [`Deobfuscator`](https://github.com/MichaelRocks/paranoid)
3. Prints `Flag: <result>` in logcat

### Issue

I initially thought that the fastest way will be to install on my phone and use ADB to control the broadcasting.

I tried this but for some reason I cannot get it to print the flag.

    $ adb shell am broadcast -a com.tamu.ctf.hidden.START

Reason is because the app uses [LocalBroadcastManager which means only the app itself can send the broadcast.](https://stackoverflow.com/questions/24981014/how-to-send-a-localbroadcast-from-adb-shell).

We confirm this by checking the receivers.

    $ adb shell cmd package query-receivers --brief -a com.tamu.ctf.START
    No receivers found


### Modify APK Smali Code

So I thought of modifying the APK code.

We see this in MainActivity.smali

    .line 32
    invoke-static {p0}, Landroid/support/v4/content/LocalBroadcastManager;->getInstance(Landroid/content/Context;)Landroid/support/v4/content/LocalBroadcastManager;

    move-result-object v2

    invoke-virtual {v2, v1, v0}, Landroid/support/v4/content/LocalBroadcastManager;->registerReceiver(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)V

    .line 34

It corresponds to this Java code.

    v2 = LocalBroadcastManager.getInstance(this)
    // invoke-static {p0 = this}

    v2.registerReceiver          // invoke-virtual {v2}
           (paramBundle, localIntentFilter); {v1, v0}

---

####  Attempt #1 (Failed)

I assumed I could simply change `LocalBroadcastManager.getInstance(this).registerReceiver()` into  `Context.registerReceiver()`, so that it will be globally registered

    // I change this:
    invoke-virtual {v2, v1, v0}, Landroid/support/v4/content/LocalBroadcastManager;->registerReceiver(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)V

    // into this:
    invoke-virtual {p0, v1, v0}, Landroid/content/Context;->registerReceiver(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)V

However, it caused a force-close upon opening the app.

---

####  Attempt #2 (Working)

I decided to simply call the `Log.d()` function to print the flag upon opening the app

From MainActivity$1.smali, I extracted the code between line 26 and 27

    .line 26
    iget-object v0, p0, Lcom/tamu/ctf/hidden/MainActivity$1;->this$0:Lcom/tamu/ctf/hidden/MainActivity;

    const v1, 0x7f0b0020

    invoke-virtual {v0, v1}, Lcom/tamu/ctf/hidden/MainActivity;->getString(I)Ljava/lang/String;

    move-result-object v0

    const/4 v1, 0x0

    invoke-static {v1}, Lio/michaelrocks/paranoid/Deobfuscator$app$Debug;->getString(I)Ljava/lang/String;

    move-result-object v1

    invoke-static {v0, v1}, Landroid/util/Log;->d(Ljava/lang/String;Ljava/lang/String;)I

    .line 27

Which corresponds to this Java code

    v0 = MainActivity.this.getString(2131427360) // Resource string "Flag:"
    v1 = Deobfuscator.app.Debug.getString(0)
    Log.d(v0, v1);

---

In order to simplify my life, se can form a simpler smali code by omitting the resource string

    const/4 v1, 0x0

    invoke-static {v1}, Lio/michaelrocks/paranoid/Deobfuscator$app$Debug;->getString(I)Ljava/lang/String;

    move-result-object v1

    invoke-static {v1, v1}, Landroid/util/Log;->d(Ljava/lang/String;Ljava/lang/String;)I

And it corresponds to 

    v1 = Deobfuscator.app.Debug.getString(0) // flag
    Log.d(v1, v1)

Now I simply insert it before the return statement in the onCreate() function.

---

### Building the APK

Now we have the [new smali](MainActivity-new.smali).

Build the new APK and it (will be found inside `app/dist/app.apk`).
Then we [need to sign it](https://stackoverflow.com/questions/18589694/i-have-never-set-any-passwords-to-my-keystore-and-alias-so-how-are-they-created) & install it

    $ apktool b app

    $ jarsigner -keystore ~/.android/debug.keystore -storepass android app/dist/app.apk androiddebugkey

    # adb uninstall com.tamu.ctf.hidden

    $ adb install app/dist/app.apk

    # adb logcat

### Solving

Now run the app and we see the flag

    02-23 16:02:16.472 18046 18046 D gigem{hidden_81aeb013bea}: gigem{hidden_81aeb013bea}

## Flag

    gigem{hidden_81aeb013bea}
