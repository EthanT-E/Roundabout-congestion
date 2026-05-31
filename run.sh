#!/bin/bash

echo "Enter the number of iterations"
read iter

./a.out $iter
python analysis.py
