#!/usr/bin/python3
import cgi, os, sys, time

form = cgi.FieldStorage()

# Get filename here.
if 'filename' in form:
	fileitem = form['filename']
else:
	print("filename not Found", file=sys.stderr)
	sys.exit(1) # Exit Fail

dirUpload = "./upload/"
if fileitem.filename:
   # if (os.path.exists(upload_dir) == False):
   #      os.makedirs(upload_dir)
   fn = os.path.basename(fileitem.filename)
   # if (os.path.isfile(dirUpload + fn) == True):
   #    print(" File have already exist")
   #    # sys.exit(1)
   # else:
   f = open(dirUpload + fn, 'wb').write(fileitem.file.read())
   message = 'The file "' + fn + '" was uploaded successfully'
   # f.close()
else:
   message = 'No file was uploaded'

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
# print(f'<h1> "form : {form}" </h1>')
print(f'<h1> "{message}" </h1>')
print('</body>')
   