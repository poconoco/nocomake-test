# Dial-up login into system via modem

Let's assume the modem is conneted to `/dev/ttyUSB0`

We need to install `mgetty`:
```
sudo apt install mgetty
```

Then configure it for our modem:
```
sudo nano /etc/mgetty/mgetty.config
```

Remove the comments and examples and reduce the contents to something like this:

```
debug 4
issue-file /etc/issue.mgetty

port ttyUSB0
  speed 115200
  data-only yes
  toggle-dtr yes
```

Then wrap it into a systemd service:

```
nano /etc/systemd/system/mgetty@ttyUSB0.service
```

Put the following there:

```
[Unit]
Description=Mgetty on %I
After=network.target

[Service]
ExecStart=/sbin/mgetty -s 115200 %I
Restart=always

[Install]
WantedBy=multi-user.target
```

Save, then reload systemctl services:
```
sudo systemctl daemon-reexec
```

And run your new mgetty service:
```
sudo systemctl start mgetty@ttyUSB0.service
```

If you want this service to start automatically, enable it:
```
sudo systemctl enable mgetty@ttyUSB0.service
```

If you want to stop and/or disable automatic start:
```
sudo systemctl stop mgetty@ttyUSB0.service
sudo systemctl disable mgetty@ttyUSB0.service
```
