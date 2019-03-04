def egcd(a, b):
    x,y, u,v = 0,1, 1,0
    while a != 0:
        q, r = b//a, b%a
        m, n = x-u*q, y-v*q
        b,a, x,y, u,v = a,r, u,v, m,n
        gcd = b
    return gcd, x, y

def main():

    p = 509
    q = 4973
    e = 43
    ct = [906851,991083,1780304,2380434,438490,356019,921472,822283,817856,556932,2102538,2501908,2211404,991083,1562919,38268]

    # compute n
    n = p * q

    # Compute phi(n)
    phi = (p - 1) * (q - 1)

    # Compute modular inverse of e
    gcd, a, b = egcd(e, phi)
    d = a
    # print( "n:  " + str(d) );

    # Decrypt ciphertext
    flag = ''
    for c in ct:
        pt = pow(c, d, n)
        print( "pt: " + str(pt) )



if __name__ == "__main__":
    main()