#!/usr/bin/python3

# Import modules for CGI handling
import cgi, cgitb

# Create instance of FieldStorage
form = cgi.FieldStorage()
 
# Get data from fields
first_name = form.getvalue('first_name')
last_name = form.getvalue('last_name')

print("Content-type:text/html")
print()
print("<html>")
print('<head>')
print("<title>Hello - Second CGI Program</title>")
print('<style>h1 {text-align: center; font-size: 40px;}</style>')
print('</head>')
print('<body>')
print(f"<h1>Hello {first_name} {last_name} </h1>")
print('</body>')
print('</html>')