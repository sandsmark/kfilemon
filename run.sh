#!/bin/sh
make
LD_PRELOAD=$PWD/libkfilemon.so $@
