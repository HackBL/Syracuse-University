#!/bin/bash

grep -c processor /proc/cpuinfo > cpuinfo.txt # Total number of processors
grep processor /proc/cpuinfo | awk '{print $3}' >> cpuinfo.txt # Processor id
grep "cache size" /proc/cpuinfo | awk '{print $4}' >> cpuinfo.txt # cache size
