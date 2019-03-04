#!/usr/bin/env sage

# Curve parameters
_prime = 412220184797
_a = 10717230661382162362098424417014722231813
_b = 22043581253918959176184702399480186312
p = _prime
E = EllipticCurve(FiniteField(p), [_a, _b])

# Generator
_Gx = 56797798272
_Gy = 349018778637
g = E(_Gx,_Gy)

# Public Keys
Pub_A = (61801292647, 228288385004)
Pub_B = (196393473219, 35161195210)

qA = E(Pub_A[0], Pub_A[1])
qB = E(Pub_B[0], Pub_B[1])

# Solve for discrete log
dA = g.discrete_log(qA)
print('Private Key A:', dA)

dB = g.discrete_log(qB)
print('Private Key B:', dB)

# Solve for shared key
SharedA = (dB * qA)
SharedB = (dA * qB)
SharedX = (dA * dB * g)
assert SharedA == SharedB and SharedB == SharedX
print('Shared Key:', SharedA)
