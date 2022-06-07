import os, random, os.path
from os import path
#init_path = "/home/ruslan/"
end_point = 20
init_path = "/"
i = 0
while os.path.isdir(init_path) or i >= end_point:
	init_path = init_path + random.choice(os.listdir(init_path)) + "/"
init_path = init_path[:-1]
print("Random path: " + init_path)
file_name = os.path.split(init_path)[1]
print("File name to search: " + file_name)

import time
for i in range(3,9):
	prog_call ="./output.out '%s' %s" % (file_name, i)
	start = time.time()
	output = os.popen(prog_call).read() 
	end = time.time()
	print("Execution time is '%f'"  %(end - start))
	print("Expected: " + init_path + "\nActual: " + output)
	if init_path in output + '\n':
		print("Test passed")
	else:
		print("Test failed")
