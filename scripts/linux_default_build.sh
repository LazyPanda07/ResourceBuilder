#!/bin/bash

set -e

rm default.so
rm tem.cpp
./resource_builder g++ default --keep default.jpg
