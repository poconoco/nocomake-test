# Requirements

This is to be runned on raspberry pi or similar system that has access to i2c

# Preparation

## Create venv

```
python3 -m venv .venv
```

## Activate venv

```
source .venv/bin/activate
```

## Install dependencies

```
python -m pip install -r requirements.txt
```

# Test angles script

This script is to find your angles and directions to konfigure IK3DOF class 
angular parameters.

```
python test_angles.py
```

Tweak the angles in the `test_angles.py` code untill you get the correct 
alignment, then use result values for IK3DOF class instance parameters
in the `run.py`

# Run

```
python run.py
```
