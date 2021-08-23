import sys

print "\n"
if len(sys.argv) < 2:
	print "Usage: python sortCheck.py [name of file to check]"
	exit(0)
	
fileName = sys.argv[1]

lines = []
try:
	with open(fileName, 'r') as f:
		lines = f.read().splitlines()
except IOError:
	print "The file " + fileName + " does not exist."
	exit(0)
		
firstStudent = lines[0].split("\t")
prevOriginal = float(firstStudent[1])
prevAdjusted = float(firstStudent[2])
originalSorted = True
adjustedSorted = True

for c in lines[1:]:
	curStudent = c.split("\t")
	if float(curStudent[1]) > float(prevOriginal):
		originalSorted = False
	if float(curStudent[2]) > float(prevAdjusted):
		adjustedSorted = False
	if not originalSorted and not adjustedSorted:
		break
	prevOriginal = curStudent[1]
	prevAdjusted = curStudent[2]

if originalSorted:
	print "The list in " + fileName + " is sorted by original grade"
else:
	print "The list in " + fileName + " is NOT sorted by original grade"
	
if adjustedSorted:
	print "The list in " + fileName + " is sorted by adjusted grade"
else:
	print "The list in " + fileName + " is NOT sorted by adjusted grade"
	
if not originalSorted and not adjustedSorted:
	print "Warning: Neither list is sorted"
