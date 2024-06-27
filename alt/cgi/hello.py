#!/usr/bin/python3

import cgi, cgitb
import sys

def main():
    print("Content-Type: text/html\n")
    print("<html><body>")
    form = cgi.FieldStorage()
    # print(form)
    if "name" not in form or "age" not in form:
        print("<h1>Error</h1>")
        print("Please fill out the name and age fields.")
    else:
        name = form.getvalue("name")
        age = form.getvalue("age")
        print(f"<h1>Hello, {name}!</h1>")
        print(f"<p>You are {age} years old.</p>")
    
    print("</body></html>")

if __name__ == "__main__":
    main()
