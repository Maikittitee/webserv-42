#!/opt/homebrew/bin/python3
import sys

# Function to read all data from standard input
def read_stdin():
    input_data = sys.stdin.read()
    return input_data

# Start the response to the client
print("Content-Type: text/plain\n")

# Read and print the data from standard input
data = read_stdin()
print("Received Data:")
print(data)