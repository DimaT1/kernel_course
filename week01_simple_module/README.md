# Simple kernel module

This module implements a simple linear congruential generator.

## Build

```sh
make
sudo make install
```

## Usage

Data is transfered using 4-byte strings. `echo` is used to set random seed.

```sh
cat /dev/uglyrandom
echo "4242" >> /dev/uglyrandom
```
