#!/opt/homebrew/bin/python3
import cgi


f = cgi.FieldStorage()

print("Content-type: text/html" )
print()

vars = f.keys()
for v in vars:
    print('%s = %s<br>' %(v,f[v].value))