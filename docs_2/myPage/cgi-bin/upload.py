#!/usr/bin/python3
import cgi, os, sys, time

form = cgi.FieldStorage()

# Get filename here.
if 'filename' in form:
	fileitem = form['filename']
else:
	print("filename not Found", file=sys.stderr)
	sys.exit(1) # Exit Fail

upload_dir = "../upload/"

# if not os.path.exists(upload_dir_2):
#     os.makedirs(upload_dir_2)
if fileitem.filename:
	# if (os.path.exists(dir_upload_2) == False):
	# 	os.makedirs(dir_upload_2)
	fn = os.path.basename(fileitem.filename)
	if (os.path.isfile(upload_dir + fn) == True):
		message = " File have already exist"
	else:
		f = open(upload_dir + fn, 'wb').write(fileitem.file.read())
		message = 'The file "' + fn + '" was uploaded successfully'
	# f.close()
else:
   message = 'No file was uploaded'

existing_files = os.listdir(upload_dir)


print("Content-Type: text/html")

print("Status: 201 Created")

print("")

print("<!DOCTYPE html>")
print('<html lang="en">')
print("<head>")
print('<meta charset="UTF-8">')
print('<meta name="viewport" content="width=device-width, initial-scale=1.0">')
print('<title>Document</title>')
print('<style>h1 {text-align: center; font-size: 40px;}</style>')
print('</head>')
print('<body>')
# for file in existing_files:
#     print(f'<li>file : {file}</li>')
# print(f'<h1> "form : {form}" </h1>')
print(f'<h1> "{message}" </h1>')
# print("<a href=\"/cgi-bin/list.py\">Go Back</a>")
print("<a href=\"/../index.html\">Go Back</a>")
print('</body>')

 