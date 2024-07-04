#!/usr/bin/python3
import os
import sys

upload_dir = os.getcwd() + "/file_pool/"
mylist = []
found = True

if os.path.exists(upload_dir) and os.path.isdir(upload_dir):
	found = True
	for filename in os.listdir(upload_dir):
		# create bottom for download
		sublist = []
		sublist.append('<a href="' + upload_dir + filename + '"download>')
		sublist.append(filename)
		sublist.append("</a>")
		mylist.append(sublist)
else:
	found = False

def listToString(s):
	str1 = ""
	for ele in s:
		str1 += ele
	return str1

print(f"working directory: {os.getcwd()}", file=sys.stderr)

print("Content-Type: text/html")

print("")

print("<!DOCTYPE html>")
print("<html><head>")
print("<title>Upload files</title>")
print("<style>")
print('html{background-color:  #fbddec;}')
print('a {color: #000000; text-decoration: none;}')
print('h2 {text-align: center;}')
print('.bottom {display: flex; flex-direction: column; text-align: center;}')
print("</style>")
print("</head>")
print("<body>")
if found:
	print('<br>')
	print("<h2> List file </h2>")
	print('<br>')
	print('<div class="bottom">')
	for i in mylist:
		# print(f"<h2>{type(i)}</h2>")
		print(f"{listToString(i)}")
	print("</div>")
else :
	print(f"<h2> Not found </h2>")
	
print("</body>\n</html>")