# GB CPU instructions implementation

def impl_LD_R_R(op, instruction, s):
	s.append( "\t{} = {};".format(op["param1"], op["param2"]) )
	s.append( "\treturn {};".format(op["cycles"])  )

def impl_LD_R_N(op, instruction, s):
	impl_LD_R_R(op, instruction, s)

def impl_Load_8bit(op, instruction, s):
	s.append( "\t{} = {};".format(op["param1"], op["param2"]) )
	s.append( "\treturn {};".format(op["cycles"])  )