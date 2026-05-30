# Potato benchmark

Intended to be run on old unix systems. Required programs in the system:

 * make
 * g++
 * time

Uses 32 bit or 64 bit ints (although if your system is too weird, 
int size may be different and you'll need to watch for it)

# Usage

Run a single pass with 32 bit ints:
```
make run
```

Run a single pass with 64 bit ints:
```
make run64
```

You also can have multiple passes for faster systems, like 10 passes:
```
make run MULT=10
```

Or even 100:
```
make run64 MULT=100
```

Or any other number of multiplication and expect the execution time measuerd 
to grow proportionally. 

# Results

| CPU | Frequency, MHz | 32-bit test time, s | 64-bit test time, s |
| :--- | :--- | :--- | :--- |
| Intel 486DX4 | 75 | 40.5 | 81 |
| Pentium MMX | 200 | 4.6 | 10.7 |
| Broadcom BCM2837 (Raspberry Pi 3) | 1200 | 0.95 | 0.95 |
| Allwinner H618 (Orange Pi Zero3) | 1415 | 0.78 | 0.78 |
| AMD Ryzen 5 5500 | 4268 | 0.068 | 0.068 |
