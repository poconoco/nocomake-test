# Simple benchmark

Intended to be run on potato unix systems
Required programs in the system:

 * make
 * g++
 * time

Uses 32 bit or 64 bit ints (although if your system is too weird, 
int size may be too different and you'll need to watch for it)

# Usage

Run single pass with 32 bit ints:
```
make run
```

Run single pass with 64 bit ints:
```
make run64
```

You also can have multiple passes for faster systems, like ten passes:
```
make run MULT=10
```

Or even 100:
```
make run64 MULT=100
```

Or any other number of multiplicationm, and expect the execution time measuerd 
to grow proportionally.
