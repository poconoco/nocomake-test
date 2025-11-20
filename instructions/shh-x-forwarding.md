# X Windows apps running remotely

X windows system allows to run apps over the network. It can be wired manually by mesing with port forwarding and DISPLAY end var, but ssh supports it natively with minor setup (which is required for DISPLAY env var way anyway).

## On the server (aka X-Client) you will run apps on

### Install some software
```
sudo apt install xauth x11-apps
```
And may be an app to test with:
```
sudo apt install xbill
```

### Adjust ssh daemon config
Edit the `/etc/ssh/sshd_config` file, find and uncomment the following lines:
```
X11Forwarding yes
X11DisplayOffset 10
X11UseLocalhost yes
```
(Only the latter two were commented out in my armbian server system)
Restart the ssh daemon:
```
sudo systemctl restart ssh
```

## On the client (aka X-Server) side

### Connect via ssh with -Y flag
Ssh supports flag for forwarding X Window connections with a simple flag `-Y`:
```
ssh user@192.167.1.123 -Y
```

And now you can run not just the console apps, but graphical as well, like the classic `xbill` game we installed for testing. It will run on the server, but will send its UI to the client and grab mouse and keyboard events from the client as well.

But it will work not just for simple and old apps like `xbill` or `xeyes`, it will also work for modern big apps like firefox. It's a replacement for VNC in a way, but sends data per window. And for legacy apps designed with X system in mind (that are not drawing their UI as a bunch of raster images, but that use simple geometry drawing operations) will work with great speed. And they will embed into your window manager nicely.
