# Building openssh for old Linux system

Tested on:
- Red Hat Linux 6.0 (1999), kernel 2.2.5
- Mandrake Linux 7.2 (2000), kernel 2.2.17

## Building Open SSL

Unpack provided [openssl-1.0.1.tar.gz](openssl-1.0.1.tar.gz):
```
tar -xzvf openssl-1.0.1.tar.gz
cd openssl-1.0.1
```

Configure:
```
./config 386 no-asm
```

Make and make install (the latter must be executed from the root user):
```
make
make install
```

## Build Open SSH

Unpack provided [openssh-6.7p1.tar.gz](openssh-6.7p1.tar.gz):

```
tar -xzvf openssh-6.7p1.tar.gz
cd openssh-6.7p1
```

Configure:
```
./configure --with-ssl-dir=/usr/local/ssl LDFLAGS="-ldl" --without-zlib-version-check
```

On a bit newer Linux system (Mandrake Linux 7.2) I also stumbled upon compilation error around `getsubopt` redefinition. I had to patch it manually by editing the `openbsd-compat/getopt.h` file, and commenting the line 64 which defines the `getsubopt` function, because this definition conflicted with stdlib header.This step was not needed on an older linux distro - Red Hat Linux 6.0.

Make and make install (latter to be executed form root):
```
make
make install
```

Now you should have `/usr/local/bin/ssh`, and you can connect to modern ssh servers with:
```
/usr/local/bin/ssh username@hostname-or-ip.com
```

