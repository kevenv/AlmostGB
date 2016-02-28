"""
	GB's CPU opcodes generator

	Script that generate all the GB's CPU opcodes
	implementation in C++

"""
from os import listdir
from os.path import isfile, join
from copy import deepcopy

import opcodes_impl

"""
	GLOBALS
"""
OP_DEF_PATH = "op/"
OP_IMPL_PATH = "impl/"
OP_STR_PATH = "str/"
OP_GEN_PATH = "../../src/gen/"
OP_IMPL_CPP_PATH = OP_GEN_PATH + "opcodes_impl.cpp"
OP_STR_CPP_PATH = OP_GEN_PATH + "opcodes_str.cpp"

processed_opcodes = []

# get list of instructions
def fillInstructionsList():
	files = [f for f in listdir(OP_DEF_PATH) if isfile(join(OP_DEF_PATH, f))]

	instructions = []
	for f in files:
		instr = {
			"name": f.split(".")[0],
			"opcodes": []
		}
		instructions.append(instr)

	return instructions

def gen_opcodes(instructions):
	for i in instructions:
		opcodes = fillOpcodes(i)
		#gen_opcodes_impl(opcodes, i)
		gen_opcodes_str(opcodes, i)

def fillOpcodes(instr):
	opcodes = []

	# read instruction definition
	with open(OP_DEF_PATH + instr["name"] + ".op", "r") as file:
		line = " "
		while line != "":
			line = file.readline()
			if line == "":  break #EOF
			elif line == "\n": continue	#skip empty lines

			line = clean_opcode_line(line)
			op = tokenize_opcode_line(line)

			if op == None: continue #skip unassigned opcode
			if not op["op"] in processed_opcodes: #remove duplicates
				opcodes.append(op)
				processed_opcodes.append(op["op"])
				print(op)

	return opcodes

def clean_opcode_line(line):
	#remove superflous spaces
	idx = line.find("(")
	idx_end = line.find(")")
	if idx != -1 and idx_end != -1:
		idx_space = line.find(" ", idx)
		if idx_space != -1:
			line = line[:idx+1] + line[idx_space+1:]

	#remove ','
	line = line.replace(",", " ")

	return line

def tokenize_opcode_line(line):
	#split
	tokens = line.split(" ")
	tokens = [x for x in tokens if x] #remove empty

	op = {}
	op["str"] = tokens[0]
	op["param1"] = tokens[1]
	op["nbParams"] = get_nb_params(op, tokens)
	
	if(op["nbParams"] == 0):
		if(tokens[3] == "??"):
			return None
		op["op"] = int(tokens[3], 16)
		op["cycles"] = int(tokens[4])

	elif(op["nbParams"] == 1):
		if(tokens[2] == "??"):
			return None
		op["op"] = int(tokens[2], 16)
		op["cycles"] = int(tokens[3])
	else:
		op["param2"] = tokens[2]
		if(tokens[3] == "??"):
			return None
		op["op"] = int(tokens[3], 16)
		op["cycles"] = int(tokens[4])

	return op

def get_nb_params(op, tokens):
	if(op["param1"] == "-/"):
		return 0
	elif(len(tokens) == 4):
		return 1
	else:
		return 2

def gen_opcodes_impl(opcodes, instr):
	with open(OP_IMPL_PATH + "op_" + instr["name"] + ".cpp", "w") as file:
		for op in opcodes:
			gen_opcode_impl(op, instr, file)

def gen_opcode_impl(op, instr, file):
	s = []
	s.append(  "case {:#x}:".format(op["op"])  )

	op_tmp = deepcopy(op)

	params = []
	p = parse_param(op["param1"],1)
	params.append(p)
	p = parse_param(op["param2"],2)
	params.append(p)

	for p in params:
		#if(p["type"] == "reg"):

		if(p["type"] == "imm"):
			if(p["size"] == 8):
				s.append( "\tn8 = m_MMU->read8(PC++);" );
			else:
				s.append( "\tn16 = m_MMU->read16(PC+=2);" );
		elif(p["type"] == "(reg)"):
			if(p["write"]):
				s.append( "\tn8 = m_MMU->read8(PC++);" );
			else:
				s.append( "\tn8 = m_MMU->read8(PC++);" );
		elif(p["type"] == "(imm)"):
			if(p["size"] == 8):
				s.append( "\tn8 = m_MMU->read8(PC++);" );
			else:
				s.append( "\tn16 = m_MMU->read16(PC+=2);" );



	if(op["param1"] == "#"):
		op_tmp["param1"] = "A"
		s.append( "\tn8 = 0; *((int*)(n8));" );
	if(op["param2"] == "#"):
		op_tmp["param2"] = "A"
		s.append( "\tn8 = 0; *((int*)(n8));" );



	evalStr = "opcodes_impl.impl_" + instr["name"] + "(op_tmp, instr, s)"
	try:
		eval(evalStr)
		str = ""
		for l in s:
			str = str + l + "\n"
		#print(str)
		file.write(str)
	except:
		print(evalStr + " failed, skipping")

def parse_param(param,id):
	p = {}
	p["param"] = param

	if("(" in p["param"]):
		p["type"] = "indirect"
		p["param"] = param.replace("(","").replace(")","")
	else:
		p["type"] = "direct"

	if(p["type"] == "direct"):
		if(param_is_imm(p)):
			p["type"] = "imm"
			p = parse_param_imm(p)
		else:
			p["type"] = "reg"
	else:
		if(param_is_imm(p)):
			p["type"] = "(imm)"
			p = parse_param_imm(p)
		else:
			p["type"] = "(reg)"

	if(id == 1):
		p["write"] = True
	else:
		p["write"] = False

	return p

def param_is_imm(p):
	return len(p["param"]) > 3

def parse_param_imm(p):
	if(p["param"] == "n"):
		p["size"] = 8
		p["param"] = "n8"
	elif(p["param"] == "nn"):
		p["size"] = 16
		p["param"] = "n16"
	return p

def gen_opcodes_str(opcodes, instr):
	with open(OP_STR_PATH + "op_" + instr["name"] + ".txt", "w") as file:
		for op in opcodes:
			gen_opcode_str(op, instr, file)

def gen_opcode_str(op, instr, file):
	str = ("case {:#x}: return \"" + opcode_str(op, instr) + "\";").format(op["op"])
	#print(str)
	file.write(str + "\n")

def opcode_str(op, instr):
	n = op["nbParams"]
	if(n == 0):
		s = "{}".format(op["str"])
	elif(n == 1):
		s = "{} {}".format(op["str"], op["param1"])
	elif(n == 2):
		s = "{} {},{}".format(op["str"], op["param1"], op["param2"])
	return s

# merge all opcodes impl into 1 cpp file
def merge_all_op_impl():
	merge_all_op(OP_IMPL_PATH, OP_IMPL_CPP_PATH)

# merge all opcodes str into 1 cpp file
def merge_all_op_str():
	merge_all_op(OP_STR_PATH, OP_STR_CPP_PATH)

def merge_all_op(src_path, dst_path):
	with open(dst_path, "w") as dst_file:
		files = [f for f in listdir(src_path) if isfile(join(src_path, f))]
		for f in files:
			merge_file(dst_file, src_path, f)

def merge_file(dst_file, src_file_path, src_file_name):
	with open(src_file_path + src_file_name, "r") as file:
		file_write_lines(dst_file, src_file_name, file.readlines())

def file_write_lines(dst_file, src_file_name, lines):
	dst_file.write("// " + src_file_name.split(".")[0] + "\n")
	for l in lines:
		dst_file.write(l)
	dst_file.write("\n")

"""
	MAIN
"""
instructions = fillInstructionsList()

gen_opcodes(instructions)

merge_all_op_impl()
merge_all_op_str()