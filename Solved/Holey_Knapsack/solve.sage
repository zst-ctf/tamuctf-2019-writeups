#!/usr/bin/env sage
import binascii


def bin2ascii(b):
    n = int(b, 2)
    return binascii.unhexlify('%x' % n)


def Solve_Knapsack_LLL(c, publicKey):
    nbit = len(publicKey)
    matrix_size = nbit + 1  # N + 1

    # create a large matrix of 0's (dimensions are public key length +1)
    M = Matrix(ZZ, matrix_size, matrix_size)

    # fill in the identity matrix
    for i in range(matrix_size):
        M[i, i] = 1

    # bottom right is encoded message
    M[nbit, nbit] = -c

    # right column is public keys
    for i in range(nbit):
        M[i, nbit] = publicKey[i]

    # lattice basis reduction
    result = M.LLL()
    # print result.str()

    # choose best vector
    #for i in range(matrix_size):
    #    print i, result.row(i).list()

    for i in range(matrix_size):
        mylist = result.row(i).list()

        # choose vector by only binary 1s and 0s
        condition = lambda x: x == 1 or x == 0
        good_vector = all(condition(item) for item in mylist)
        if not good_vector:
            continue

        # combine the binary string
        binary_str = ''.join(list(map(str, mylist)))

        # i guessed the plaintext starts with gigem{ format
        # hence by inspection, the bit order is reversed
        binary_str = binary_str[::-1]

        # convert  binary to ascii
        print hex(ct), mylist, binary_str, bin2ascii(binary_str)
        return bin2ascii(binary_str)

    print hex(ct), "no solution"
    # print result.str()
    return '?'


c = '11b90d6311b90ff90ce610c4123b10c40ce60dfa123610610ce60d450d000ce61061106110c4098515340d4512361534098509270e5d09850e58123610c9'
publicKey = [99, 1235, 865, 990, 5, 1443, 895, 1477]
print('sum', sum(publicKey), hex(sum(publicKey)))


flag = ''
split = 4 # every 4 chars
for i in range(0, len(c), split):
    ct = int(c[i:i+split], 16)
    # print('ct', hex(ct))

    flag += Solve_Knapsack_LLL(ct, publicKey)

print(flag)

