#############################################################################
# Program:
#    Python code showing how to take input from the command line.
#############################################################################

import sys

#############################################################################
# This is main
#############################################################################
DEFAULT_VALUE = 6789
argument1 = int(sys.argv[1]) if len(sys.argv) == 2 else DEFAULT_VALUE
print argument1


