#!/bin/bash

echo "Enter the number of iterations"
read iter
echo "Enter the number of Cars"
read car_num

./a.out $iter $car_num
python analysis.py
