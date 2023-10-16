import sys
import os

if len(sys.argv) < 2:
	filename = input("filename? ")

else:
	filename = sys.argv[1]


try:
	f = open(filename)

except:
	print("File not found")
	exit()


print("\"", end = "")

print("\\n".join(line.rstrip().replace("\"", "\\\"").replace("\t", "\\t") for line in f), end = "")

print("\"")


os.system("pause")
