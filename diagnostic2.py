# -*- coding: utf-8 -*-
"""
Created on Wed Jan 17 11:39:22 2018

@author: Lila
"""

num = int(input())
numbers = input()
numbers = numbers.split()
total = 0
big1 = int(numbers[0])
big2 = int(numbers[1])
for x in range(num):
    if int(numbers[x]) > big1:
        big2 = big1
        big1 = int(numbers[x])
    elif int(numbers[x]) > big2:
        big2 = int(numbers[x])
total = big1+big2
print(total)