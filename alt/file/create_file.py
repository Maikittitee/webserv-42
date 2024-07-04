# Open a file in write mode
file = open("example.txt", "wb")

# Write content to the file
file.write(b"Hello, this is a test file.\n")
file.write(b"This file is created using Python.\n")

# Close the file
file.close()

print(b"File created and written successfully.")
