#!/usr/bin/python3
import cgi, os, sys, time
# import cgitb; cgitb.enable()

form = cgi.FieldStorage()

# Get filename here.
if 'filename' in form:
	fileitem = form['filename']
else:
	print("filename not Found", file=sys.stderr)
	sys.exit(1) # Exit Fail

dirUpload = "./upload/"
if fileitem.filename:
   # strip leading path from file name to avoid 
   # directory traversal attacks
   # tmp = os.path.exists(upload_dir)
   # if (os.path.exists(upload_dir) == False):
   #      os.makedirs(upload_dir)
   fn = os.path.basename(fileitem.filename)
   # if (os.path.isfile(dirUpload + fn) == True):
   # if (os.path.exists(dirUpload + fn)):
   #    print(" File have already exist")
   #    # sys.exit(1)
   # else:
   f = open(dirUpload + fn, 'wb').write(fileitem.file.read())
   message = 'The file "' + fn + '" was uploaded successfully'
   # f.close()
else:
   message = 'No file was uploaded'
# tmp = 0
# tmp = os.path.exists(upload_dir)
# tmp = 1



# if fileitem.filename:
# 	fn = os.path.basename(fileitem.filename)
# 	if os.path.exists(dirUpload + fn):
# 		message = 'Files is already Exists'
# 	else:
# 		f = open(dirUpload + fn, "wb") # 'wb' for write in binary mode
# 		f.write(fn.file.read())
# 		message = 'The file "' + fn + '" was uploaded successfully'
# 		f.close()
# else:
	# message = 'No file was uploaded'



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
# print(f'<h1> "file name : {file_name}" </h1>')
# print(f'<h1> "form : {form}" </h1>')
# print(f'<h1> "form type : {type(form)}" </h1>')
# print(f'<h1> "file_item : {file_item}" </h1>')
# print(f'<h1> tmp : "{tmp}" </h1>')
print(f'<h1> "{message}" </h1>')
print('</body>')
   
# print("")

# print f"""\
# Content-Type: text/html\n
# <html>
#    <body>
#    <h1> Hello </h1>
#       <p>{message}</p>
#    </body>
# </html>
# """