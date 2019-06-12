import os

class NS:
	def __init__(self, prototype):
		self.prototype = prototype
		self.children = {}
		self.methods = {}
		
	def print(self, depth=0):
		print('\t' * depth + self.prototype)
		for key, c in self.children.items():
			c.print(depth+1)
			
		for key,m in self.methods.items():
			print('\t' * depth + m)
			
	def __getitem__(self, key):
		return self.children[key]
	
		
classes = {}

def getClass(prototype):
	global classes
	
	try:
		path = prototype.split('(')[0]
		args = prototype.split('(')[1]
		
		if '<' in path:
			return None
			
		bits = path.split('::')
		
		if len(bits) < 2 or bits[0] == 'ncm':
			return None
		
		last = None
		p = classes
		fqns = ''
		for c in bits[0:-1]:
			fqns += '::' + c
			if c not in p:
				p[c] = NS(fqns.strip(':'))
			p = p[c].children
	except BaseException as e:
		print(str(e))
		#raise
		return None
		
	

with open('symbols.txt') as f:
	lines = f.read().split('\n')
	
for line in lines:
	if line.startswith('nn::audio::AudioBufferList') or line.startswith('nn::audio::server::PerfAspect') or line.startswith('nn::audio::server::PerformanceManagerImpl'):
		continue
	getClass(line)
	'''
	path = line.split('(')[0]
	
	if '<' in path:
		continue
		
	bits = path.split('::')[1:]
	if len(bits) < 1 or bits[0] == 'ncm':
		continue
	#print(bits[-1])
	
	path = 'include/nn/' + '/'.join(bits[0:-2])
	print('::'.join(bits[0:-2]))
	print(bits[-2])

	os.makedirs(path, exist_ok=True)
	path += '/' + bits[-2] + '.h'
	
	with open(path, 'w') as f:
		f.write('#pragma once\n#include "nn.h"\n\nnamespace nn::ncm\n{\n')
		f.write('\tclass ' + bits[-2] + '\n\t{\n')
		f.write('\t}\n')
		f.write('}\n')
	'''

#for name,c in classes.items():
#	c.print()

classes['nn']['ncm'].print()