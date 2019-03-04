// initialise
int var_15 = 0x99;
int var_16 = 0x11;
var_8 = arg0;
int var_10 = 0x0;

while (true) {
    if (var_10 > 3) { // loc_a84:
    	// goto xor_globPass();
    	break;
    } else {
        var_14 = 0x0;

        if (var_14 > 0xf) { // loc_a91:
            // goto loc_adf:
        } else {
            while (true) {
                // loc_a97:
                var_16 = var_16 + var_14 * var_10;
                var_8 += 1;
                if (0x99 != (var_8 & 0xff ^ 0x55)) {
                    // at loc_ac7;
                    var_16 = var_16 - var_14 * var_10;
                    var_14 = var_14 + 0x1;
                    
                    // at loc_a91;
                    if (var_14 > 0xf) {
                        // at loc_adf;
                        var_10 += 1;
                        break;
                    } else {
                        // goto loc_a97 / continue
                    }
                }
            }
        }

        // at loc_adf:
        var_10 += 1;
        continue; // while loop
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
