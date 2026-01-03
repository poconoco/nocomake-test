# Connecting Windows 95 or NT or Linux to Linux server/router

## Configure pppd on the host linux system

Install pppd with:
```
sudo apt install ppp
```

Edit `/etc/ppp/options`. In the configuration below, modify if needed:

- `/dev/ttyUSB0` - your modem serial port
- `19200` - port speed. Linux server can handle any up to 115200. But 19200 is Windows 95 default, and changing it may be a bit tricky. You need to connect on 19200, then
  change speed of the port in the device manager, then in the "Modems" you'll see the modem for this connection, like "Serial cable on COM1", open it, and change port
  speed to faster as well. Then reboot (!). Windows will not request it, but the setting will work for direct connection only after rebooting. In the end, the port speeds on the linux
  server and windows client should match. I got it connected on 115200, but connection was unreliable, while the speed 57600 gave me reliable connection.
- `192.168.1.1` - your local router DNS or
- `192.168.3.201:192.168.3.202` - this is local:remote addresses to be assigned for the ppp interface. Should not clash with your local network


```
/dev/ttyUSB0
19200
connect 'chat TIMEOUT 20000 CLIENT CLIENTSERVER'
nodetach
debug
dump
noauth
netmask 255.255.255.0
proxyarp
192.168.3.201:192.168.3.202
ms-dns 192.168.1.1
lock
passive
lcp-echo-interval 8
lcp-echo-failure 6
nologfd
crtscts
local
```

Then run pppd to wait for the conenction with the simple:
```
pppd
```
I had to do it either with sudo or root, because lazy to configure ports groups/permissions. This wilkl work for one connection session only, if you disconnect, it will quit, and youl'l need to start pppd again. Or use a bash loop. The persist option didn't work for me. The pppd daemon won't quit after disconnection, but win client could not connect again untill I restart pppd anyway.

## Windows client

See above note about the speed. If you don't need max speed, you can skip it and just use 19200 for a start. Then go to Start->Programs->Accessories->Direct Cable Connection

Select "Guest", select the COM port your null modem cable is connected to, and hit connect.

## Linux client

On the linux client side you only need a pppd, configure it by creating the file `/etc/ppp/peers/direct` (I just used "direct" name, you can use your own, and reference it below)

Put the following contents, adjusting your port address to where your cable is connected and port speed to match one on the server side. Between two linuxes I had stable connection at the speed 115200. If you use 115200, also set the same speed on the server side!

```
/dev/ttyS0
115200
connect "/usr/sbin/chat -v '' TIMEOUT '' CLIENT CLIENTSERVER"
crtscts
noauth
defaultroute
usepeerdns
persist
```

Note that the chat line is set to chat with the coorresponding line from the server. And when you do linux<->linux conection, you can just remove chat lines. It's on the server only to mimic the Win95 direct cable connection host. And on the linux client I made it to match so the server can respnd to both windows and linux.

And then do from root (or with sudo if you have one or fix port permissions)
```
pppd call direct
```

You can observe the connection progress by tailinbg the system messages log file (also from root):
```
tail -f /var/log/messages
```

That will establish the connection.
