import os

classes = {}

def getClass(path):
	global classes
	
	try:			
		bits = path.split('::')
		
		if len(bits) < 2 or bits[0] == 'ncm':
			return None
		
		last = None
		p = classes
		fqns = ''
		for c in bits:
			fqns += '::' + c
			if c not in p:
				p[c] = NS(fqns.strip(':'))
			last = p[c]
			p = p[c].children
			
		return last
	except BaseException as e:
		print(str(e))
		raise
		return None
		
		
def addMethod(prototype):
	try:
		path = prototype.split('(')[0]
		args = prototype.split('(')[1]
		
		if '<' in path:
			return None
		
		bits = path.split('::')
		
		c = getClass('::'.join(bits[0:-1]).strip('::'))
		
		if c:
			c.methods[prototype] = Method(prototype)
	except:
		#raise
		pass

class Method:
	def __init__(self, prototype):
		self.prototype = prototype
		self.base = prototype.split('(')[0].split('::')[-1]
		self.parseArgs(prototype.split('(', 1)[1][0:-1])
		
	def generatePrototype(self, indent=0):
		return '\t' * indent + str(self) + '(' + ', '.join(self.args) + ');'
		
	def parseArgs(self, args):
		self.args = []
		last = ''
		inTemplate = 0
		for c in args:
			if inTemplate == 0 and c == ',':
				if last != '':
					self.args.append(last.srip())
					last = ''
			else:
				last += c
			if c == '<':
				inTemplate += 1
			elif c == '>':
				inTemplate -= 1
			
				
		if len(last) and last != 'void':
			self.args.append(last.strip())
			
		for a in self.args:
			if a.startswith('nn::'):
				getClass(a.split(' ')[0].strip('&'))
			
		
	def __str__(self):
		return self.base

class NS:
	def __init__(self, prototype):
		self.prototype = prototype
		self.base = prototype.split('(')[0].split('::')[-1]
		self.children = {}
		self.methods = {}
		
	def __str__(self):
		return self.base
		
	def headerPath(self):
		return 'include/' + '/'.join(self.prototype.split('(')[0].split('::')) + '.h'
		
	def createHeaderDir(self):
		path = 'include/' + '/'.join(self.prototype.split('(')[0].split('::')[0:-1])
		os.makedirs(path, exist_ok=True)
		
		
	def print(self, depth=0):
		print('\t' * depth + str(self))
		for key, c in self.children.items():
			c.print(depth+1)
			
		for key,m in self.methods.items():
			print('\t' * (depth+1) + '*' + str(m) + ' ' + ', '.join(m.args))
			
	def definition(self, indent=0):
		tabs = '\t' * indent
		structs = []
		methods = []
		for key,c in self.children.items():
			if c.isStruct():
				structs.append(c.definition(indent+1))
				
		for key,m in self.methods.items():
			methods.append(m.generatePrototype(indent+1))
			
		structs = '\n'.join(structs)
		methods = '\n'.join(methods)
		content = (structs + '\n' + methods).strip()
		if content:
			content += '\n'
		return f'{tabs}class {self.base}\n{tabs}{{\n' + content +  f'{tabs}}}\n'
			
	def generate(self):
		self.createHeaderDir()
		
		with open(self.headerPath(), 'w') as f:
			f.write(f'''#pragma once
#include "nn.h"
''' + self.definition())

		for key, c in self.children.items():
			c.generate()
		
	def isStruct(self):
		return len(self.children) == 0 and len(self.methods) == 0
			
	def __getitem__(self, key):
		return self.children[key]

with open('symbols.txt') as f:
	lines = f.read().split('\n')
	
for line in lines:
	if line.startswith('nn::audio::AudioBufferList') or line.startswith('nn::audio::server::PerfAspect') or line.startswith('nn::audio::server::PerformanceManagerImpl'):
		continue
	addMethod(line)
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

classes['nn'].print()
classes['nn'].generate()