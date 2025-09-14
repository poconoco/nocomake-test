# Dialup ISP on armbian

## Server setup (the system that will accept calls)

### Configure mgetty to pick up calls to your modem

Follow the instructions in the [dialup-login.md](dialup-login.md) - they are for remote login, but they are also work for ppp dial-in, with the addition of steps below

### Configure mgetty for pppd

Edit file `/etc/mgetty/login.config`, enable automatic PPP detection by uncommenting or adding/changing this line:

```
/AutoPPP/ - a_ppp /usr/sbin/pppd
```

This tells mgetty to launch pppd when it detects a PPP LCP packet instead of a text login.

### Setup ppp

```
sudo apt install ppp
```

Edit `/etc/ppp/options`. In the configuration below, modify if needed:

- `/dev/ttyUSB0` - your modem serial port
- `115200` - modem port speed (not the modem speed, a port speed)
- `192.168.1.1` - your local router DNS or
- `192.168.3.201:192.168.3.202` - this is local:remote addresses to be assigned for the ppp interface. Should not clash with your local network


```
/dev/ttyUSB0
115200
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

## Client setup (the system that would place a call)

### Install ppp daemon

If you are on an debian based system, use
```
sudo apt install ppp
```

I'm testing this on an old linux distro on an old i486 laptop. The distro is Red Hat Linux 6.0 (released in 1999, not to confuse with RHEL Linux 6.0). There I just installed ppp .rpm file from the folder with installable rpms copied from the install CD (because this laptop has no CD drive).

### Configure ppp

Create a file, e.g., `/etc/ppp/peers/dialup`, to configure the connection.

Given that the:
- `/dev/ttyS0` - is your modem port
- `115200` - is port speed (not to confuse with the max modem speed, port speed is higher, so for 33.6k modem, port speed is 38400, 57600 or 115200. Often it's the latter)
- `9095551010` - is the phone number of a dialup server you configured above or the ISP
- `persist` - presense of this line will make ppp daemon to redial automatically if connection is lost

The file will contain:
```
/dev/ttyS0
115200
connect "/usr/sbin/chat -v '' ATDT9095551010 CONNECT ''"
crtscts
noauth
defaultroute
usepeerdns
persist
```

### Initiate the connection

I executed it from the root user, because there is no sudo on the RH6.0 linux, and I was too lazy to configure everything properly with dedicated user. If you have sudo that should work as well.
```
pppd call dialup
```

In the legacy RH Linux 6.0 system you can observe the status of the connection by watching the messages log file:
```
tail -f /var/log/messages
```

That will display the log lines as they are written to the file in realtime, very handy.

If the connection persists, to close it, you need to kill the pppd process, like:
```
killall pppd
```
