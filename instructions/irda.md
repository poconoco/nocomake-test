# Context

IrDA support was removed in kernel 4.18-something. So to use IrDA with default kernel, chose distributive with version smaller than that.

# Installation

For example, Ubuntu 18.04, but since it got updates, you'll have to install kernek 4.15:

```
sudo apt update
sudo apt install linux-image-generic linux-headers-generic
sudo apt install irda-utils
```

Then boot into it, you probably will need to add a timeout to GRUB to select thios kernel

# Load modules and start serial

```
sudo modprobe irda
sudo modprobe ks959-sir
sudo modprobe ircomm-tty
```

Verify modules loaded and irda0 device is available
```
sudo ip link show
```

Attach as serial (untested yet)
```
sudo irattach irda0 -s
```

