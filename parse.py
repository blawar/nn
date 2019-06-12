import os
import json

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
		
		
def addMethod(name):
	try:
		path = name.split('(')[0]
		args = name.split('(')[1]
		
		if '<' in path:
			return None
		
		bits = path.split('::')
		
		c = getClass('::'.join(bits[0:-1]).strip('::'))
		
		if c:
			c.methods[name] = Method(name)
	except:
		#raise
		pass
		
class Argument:
	def __init__(self, statement):
		self.name = None
		statement = statement.strip()
		self.statement = statement
		if statement.endswith('&&'):
			self.rvalue = True
			statement = statement[0:-2].strip()
		else:
			self.rvalue = False
			
		if statement.endswith('&'):
			self.reference = True
			statement = statement[0:-1].strip()
		else:
			self.reference = False
			
		if statement.endswith('*'):
			self.pointer = True
			statement = statement[0:-1].strip()
		else:
			self.pointer = False
			
		if statement.endswith(' const'):
			self.const = True
			statement = statement[0:-6].strip()
		else:
			self.const = False
			
		self.datatype = statement
		
		if self.datatype == 'long':
			self.datatype = 's64'
		elif self.datatype == 'ulong':
			self.datatype = 'u64'
		elif self.datatype == 'int':
			self.datatype = 's32'
		elif self.datatype == 'uint':
			self.datatype = 'u32'
		elif self.datatype == 'uchar':
			self.datatype = 'u8'
		
	def __str__(self):
		if self.const:
			r = 'const ' + self.datatype
		else:
			r = self.datatype
			
		if self.pointer:
			r += '*'
			
		if self.reference:
			r += '&'
			
		if self.rvalue:
			r += '&&'
			
		
		return r
		
	def serialize(self):
		o = {}
		return {'name': self.name, 'datatype': self.datatype, 'const': self.const, 'pointer': self.pointer, 'reference': self.reference, 'rvalue': self.rvalue}

class Method:
	def __init__(self, prototype):
		self.prototype = prototype
		self.cmd = None
		self.parseArgs(prototype.split('(', 1)[1][0:-1])
		
	def base(self):
		return self.prototype.split('(')[0].split('::')[-1]
		
	def generatePrototype(self, indent=0):
		#return '\t' * indent + str(self) + '(' + ', '.join(self.args) + ');'
		return '\t' * indent + str(self) + '(' + ', '.join([str(a) for a in self.args]) + ');'
		
	def parseArgs(self, args):
		self.args = []
		last = ''
		inTemplate = 0
		for c in args:
			if inTemplate == 0 and c == ',':
				if last != '':
					self.args.append(Argument(last.strip()))
					last = ''
			else:
				last += c
			if c == '<':
				inTemplate += 1
			elif c == '>':
				inTemplate -= 1
			
				
		if len(last) and last != 'void':
			self.args.append(Argument(last.strip()))
			
		for a in self.args:
			if a.datatype.startswith('nn::'):
				getClass(a.datatype.split(' ')[0].strip('&'))
			
		
	def __str__(self):
		return self.base()
		
	def serialize(self):
		o = {}
		o['prototype'] = self.prototype
		o['cmd'] = self.cmd
		o['args'] = []
		for a in self.args:
			o['args'].append(a.serialize())
		return o

class NS:
	def __init__(self, name):
		self.name = name
		self.type = None
		self.size = None
		self.children = {}
		self.methods = {}
		
	def base(self):
		return self.name.split('(')[0].split('::')[-1]
		
	def __str__(self):
		return self.base()
		
	def headerPath(self):
		return 'include/' + '/'.join(self.name.split('(')[0].split('::')) + '.h'
		
	def createHeaderDir(self):
		path = 'include/' + '/'.join(self.name.split('(')[0].split('::')[0:-1])
		os.makedirs(path, exist_ok=True)
		
		
	def print(self, depth=0):
		print('\t' * depth + str(self))
		for key, c in self.children.items():
			c.print(depth+1)
			
		for key,m in self.methods.items():
			print('\t' * (depth+1) + '*' + str(m) + ' ' + ', '.join([str(a) for a in m.args]))
			
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
			
		base = self.base()
		
		return f'{tabs}class {base}\n{tabs}{{\n' + content +  f'{tabs}}}\n'
			
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
		
	def serialize(self):
		o = {}
		o['name'] = self.name
		o['type'] = self.type
		o['size'] = self.size
		o['children'] = {}
		o['methods'] = {}
		 
		for key,v in self.children.items():
			o['children'][key] = v.serialize()
			
		for key,v in self.methods.items():
			o['methods'][key] = v.serialize()
			
		return o
		

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

def save():
	global classes
	
	o = {}
	o['nn'] = classes['nn'].serialize()
	
	with open('classes.json', 'w') as outfile:
		json.dump(o, outfile, indent=4)
	
save()
classes['nn'].print()
classes['nn'].generate()