import pdb
from anytree import Node, RenderTree

shinygold = Node("1 shiny gold")

darkolive = Node('1 dark olive', parent=shinygold)
vibrantplum = Node('2 vibrant plum', parent=shinygold)

fadedblue = Node('3 faded blue', parent=darkolive)
dottedblack = Node('4 dotted black', parent=darkolive)
fadedblue = Node('5 faded blue', parent=vibrantplum)
dottedblack = Node('6 dotted black', parent=vibrantplum)

for pre, fill, node in RenderTree(shinygold):
	print("%s%s" % (pre, node.name))