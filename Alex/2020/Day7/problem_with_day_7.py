import pdb
from anytree import Node, RenderTree

#Setup First Node in tree
shinygold = Node("1 shiny gold")
print(shinygold)#Outputs: Node('/1 shiny gold')

##Setup child node

#This one works
child = '1 dark olive'
darkolive = Node(child, parent=shinygold)
print(darkolive)#Outputs: Node('/1 shiny gold/1 dark olive')

#This one doesn't
elder = 'shinygold'
#thisdict = {'shinygold': shinygold}
thisdict = {elder:elder}
print(thisdict)#Outputs: parent=shinygold
#pdb.set_trace()
darkolive = Node(child, parent=thisdict[elder])#Produces error: anytree.node.exceptions.TreeError: Parent node 'parent=shinygold' is not of type 'NodeMixin'.
print(darkolive)