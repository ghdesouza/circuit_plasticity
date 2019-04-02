#!/bin/bash

for i in 1 2 3
do
   for j in 1 2 3 4
   do
      for k in 1 2 3 4 5 6 7
      do
         ./main_nc.out $i $j $k
      done
   done
done
