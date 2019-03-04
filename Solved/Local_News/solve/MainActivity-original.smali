.class public Lcom/tamu/ctf/hidden/MainActivity;
.super Landroid/support/v7/app/AppCompatActivity;
.source "MainActivity.java"


# direct methods
.method public constructor <init>()V
    .locals 0

    .prologue
    .line 16
    invoke-direct {p0}, Landroid/support/v7/app/AppCompatActivity;-><init>()V

    return-void
.end method


# virtual methods
.method protected onCreate(Landroid/os/Bundle;)V
    .locals 3
    .param p1, "savedInstanceState"    # Landroid/os/Bundle;

    .prologue
    .line 20
    invoke-super {p0, p1}, Landroid/support/v7/app/AppCompatActivity;->onCreate(Landroid/os/Bundle;)V

    .line 21
    const v2, 0x7f09001a

    invoke-virtual {p0, v2}, Lcom/tamu/ctf/hidden/MainActivity;->setContentView(I)V

    .line 23
    new-instance v1, Lcom/tamu/ctf/hidden/MainActivity$1;

    invoke-direct {v1, p0}, Lcom/tamu/ctf/hidden/MainActivity$1;-><init>(Lcom/tamu/ctf/hidden/MainActivity;)V

    .line 30
    .local v1, "hidden":Landroid/content/BroadcastReceiver;
    new-instance v0, Landroid/content/IntentFilter;

    invoke-direct {v0}, Landroid/content/IntentFilter;-><init>()V

    .line 31
    .local v0, "filter":Landroid/content/IntentFilter;
    const v2, 0x7f0b0021

    invoke-virtual {p0, v2}, Lcom/tamu/ctf/hidden/MainActivity;->getString(I)Ljava/lang/String;

    move-result-object v2

    invoke-virtual {v0, v2}, Landroid/content/IntentFilter;->addAction(Ljava/lang/String;)V

    .line 32
    invoke-static {p0}, Landroid/support/v4/content/LocalBroadcastManager;->getInstance(Landroid/content/Context;)Landroid/support/v4/content/LocalBroadcastManager;

    move-result-object v2

    invoke-virtual {v2, v1, v0}, Landroid/support/v4/content/LocalBroadcastManager;->registerReceiver(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)V

    .line 34
    return-void
.end method
