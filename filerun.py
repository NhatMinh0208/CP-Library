#!/home/nhatminh0208/miniconda3/bin/python
import subprocess
import sys
# This script helps you convert file I/O to normal I/O.
# Can be used in conjunction with cf-tool.
s = sys.argv[1]
subprocess.run(['cp','/dev/stdin',f'{s}.inp']);
subprocess.run([f'./{s}']);
subprocess.run(['cat',f'{s}.out']);
