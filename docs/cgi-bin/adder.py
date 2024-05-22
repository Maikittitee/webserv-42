#!/opt/homebrew/bin/python3

import sys;

if (len(sys.argv) != 2):
	exit()

n1, n2 = list(map(int, sys.argv[1].split("&")))

print("Welcome to adder cgi example!")
print(f"{n1} + {n2} = {n1 + n2}")
