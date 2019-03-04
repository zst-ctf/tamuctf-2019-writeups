#!/usr/bin/env python

import string
from pwn import *
context(terminal = ['bash'])

charset = string.ascii_letters + string.digits

encoded = "[OIonU2_<__nK<KsK"

def main():
    keygenme = process(['gdb', './keygenme'])

    # Break program before it runs, so we can hijack it
    keygenme.recvuntil('(gdb)')
    keygenme.sendline('break main')
    keygenme.recvuntil('(gdb)')
    keygenme.sendline('run')

    # Dynamically scan for flag using call functions
    text = ''
    while len(text) < len(encoded):
        for ch in charset:
            keygenme.recvuntil('(gdb)')

            payload = text + ch
            command = 'printf "%s\\n", (char *) enc("INPUT")'.replace('INPUT', payload)
            keygenme.sendline(command)
            
            result = keygenme.recvuntil('\n')[1:-1]
            print(payload + '->' + result)

            if encoded.startswith(result):
                text += ch
                print("Success: " + text)
                break
            
    assert len(text) > 9 and len(text) <= 0x40
    print("Result: " + text)
    keygenme.kill()


if __name__ == '__main__':
    main()
