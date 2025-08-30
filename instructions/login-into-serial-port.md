# Login into system via terminal connected to serial port

Let's assume the port is `/dev/ttyUSB0`

Then we need to create new agetty service by cloning existing one:

```
sudo -i
cd /lib/systemd/system
cp serial-getty@.service serial-getty@ttyUSB0.service
nano serial-getty@ttyUSB0.service
```

And replace the `agetty` line:

```
ExecStart=-/sbin/agetty -o '-p -- \\u' --keep-baud 115200,57600,38400,9600 %I $TERM
```

With the line:

```
ExecStart=-/sbin/agetty -o '-p -- \\u' 115200 %I $TERM
```

You can use lower speed, like 9600 or even 300 if you are using real vintage terminal like VT100,
but for our purposes, the PC on teh other side can handle 115200.

Now start the service:

```
systemctl daemon-reload
systemctl start serial-getty@ttyUSB0.service
```

If you want it to start automatically, you can enable the service:
```
systemctl enable serial-getty@ttyUSB0.service
```

Now you can connect and login to the serial using either `minicom`, `picocom` or `screen` on Linux passing
the same speed, or on Windows 95 use Hyper Terminal or PyTTY for direct serial connection.

If you want to stop and/or disable automatic start:
```
systemctl stop serial-getty@ttyUSB0.service
systemctl disable serial-getty@ttyUSB0.service
```

