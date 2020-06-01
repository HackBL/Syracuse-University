#!/bin/bash
ps -ef -u $USER | grep ./infloop | awk '{print $2}' | xargs kill -9
