#!/bin/bash

python ./spec/insert_random.py | ./db data.db
rm data.db
