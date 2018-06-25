#!/usr/bin/env python
def linesof(files): return len(open(files).readlines())

from argparse import ArgumentParser
from os import system

parser = ArgumentParser()
parser.add_argument('-R', type = str)
parser.add_argument('-B', type = str)

args = parser.parse_args()

rstr = args.R
bstr = args.B

system("./../geng 2 > base.g6")
system("./../geng 2 > base2.g6")

f1 = "base.g6"
f2 = "base2.g6"

rstr.replace(" ", "")
bstr.replace(" ", "")
print rstr, bstr

while (linesof("base.g6") != 0 and linesof("base2.g6") != 0):

    temp = f1
    f1 = f2
    f2 = temp
    system("cat "+f1+" | ./addvg " + rstr + ' ' + bstr + " | ./../shortg > " + f2)
