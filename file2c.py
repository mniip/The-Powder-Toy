import sys
import re

def encode(x):
	x = x.group(0)
	if x == '\n':
		return '\\n';
	if x == '"':
		return '\\"';
	if x == '\\':
		return '\\\\';
	return '\\{0:03o}'.format(ord(x))

f = open(sys.argv[2], 'rb')

data = f.read()
f.close()
size = len(data)
data = '"' + re.sub(r'[^ -~]|"|\\', encode, data) + '"';

i = open(sys.argv[3], 'r')
o = open(sys.argv[1], 'w')
o.write(i.read().replace('/*#SIZE*/', str(size)).replace('/*#DATA*/', data))
i.close()
o.close()
