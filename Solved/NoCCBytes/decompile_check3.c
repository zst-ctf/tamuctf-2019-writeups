// initialise
int var_15 = 0x99;
int var_16 = 17 // 0x11;
var_8 = arg0;

for (int var_10 = 0; var_10 < 3; var_10++) {
    for (int var_14 = 0; var_14 <= 0xf; ) {
        // loc_a97:
        var_16 = var_16 + var_14 * var_10;
        var_8 += 1;
        if (0x99 != (var_8 & 0xff ^ 0x55)) {
            // at loc_ac7;
            var_16 = var_16 - var_14 * var_10;
            var_14++;
            
        }
    }
}

var_C = 0x0;
while (var_C <= 0x18) {
    if (arg0 == passCheck(char*)) {
        if (globPass[var_C] != 0x0) {
            globPass[var_C] ^= var_16;
        }
    }
    var_C++;
}
