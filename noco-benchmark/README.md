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

Example results:

- Red Hat Linux 6.0 on i486DX4@75Mhz laptop, 32bit test: 40.57 seconds
- Ubuntu 24.04 on Ryzen 5 5500, 64bit test: 0.06 seconds
- Same Ryzen 5 system, 10 passes: 0.68 seconds
