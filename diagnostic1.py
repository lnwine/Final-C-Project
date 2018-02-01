# -*- coding: utf-8 -*-
"""
Created on Wed Jan 17 11:27:56 2018

@author: Lila
"""

num = int(input())
numbers = input()
numbers = numbers.split()
total = 0
for x in range(num):
    total = total + int(numbers[x])
    
print(total)