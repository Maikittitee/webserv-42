#!/usr/bin/python3

import cgi, os, sys, time

form = cgi.FieldStorage()
print("Content-type: text/html")
print()
print(f"recieve form: {form}", file=sys.stderr)

# Get filename here.
if 'filename' in form:
	fileitem = form['filename']
else:
	print("no filename contained in form", file=sys.stderr)
	sys.exit(1) # Exit Fail

print(fileitem)

if fileitem.filename:
	fn = os.path.basename(fileitem.filename)
	f = open("file_pool/" + fn, 'wb')
	f.write(fileitem.file.read())
	message = 'The file "' + fn + '" was uploaded successfully'
	f.close()
else:
   message = 'No file was uploaded'

existing_files = os.listdir("file_pool")

print("Content-Type: text/html")

print("Status: 201 Created")

print("")

print("<!DOCTYPE html>")
print('<html lang="en">')
print("<head>")
print('<meta charset="UTF-8">')
print('<meta name="viewport" content="width=device-width, initial-scale=1.0">')
print('<title>Document</title>')
print('</head>')
print('<body>')
for file in existing_files:
    print(f'<h2>file : {file}</h2>')

# print(f'<h1> "form : {form}" </h1>')
print(f'<h1> "{message}" </h1>')
print('</body>')