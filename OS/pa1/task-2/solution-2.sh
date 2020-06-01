#!/bin/bash

find . -name "*.c" | xargs tar "--transform=s|.*/||g" -rf allcfiles.tar

<< 'comment'
1. find all files with extension of c
2. using xargs to call following execution
3. using transform to exclude directory structure
4. Acchive tar file 
comment



