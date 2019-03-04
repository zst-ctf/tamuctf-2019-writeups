#!/usr/bin/env python3
import pyotp
import math 
import time

# https://en.wikipedia.org/wiki/Time-based_One-time_Password_Algorithm#Implementation
# Link from QR code:
#   otpauth://totp/PACTF%3AMiles?secret=ORUW2ZK7OBQXG43FONPWE5LUL5RXK2LMONPXG5DBPFPXI2DFL5ZWC3LF

current_milli_time = lambda: int(round(time.time() * 1000))

secret = 'XMIUKUVU62MPYTSV'
timestamp = current_milli_time() # given from challenge
TS = 30*1000 # 30 sec -> millisec
TC = int(math.floor(timestamp / TS))
TOTP = pyotp.HOTP(secret)
TOTP_TC = int(TOTP.at(TC))

print('Result = %d' % TOTP_TC)