import random
import sys

# if sufficient command line arguments not passed
if len(sys.argv) != 3: 
	print("Usage: python GenerateGraph.py <number of nodes> <number of edges>")
	exit()
else:	
	# save number of nodes
	n = sys.argv[1] 
	# save number of edges
	e = sys.argv[2]	
	#formulate unique file name
	outputFileName = "graph_"+str(n)+"_"+str(e)+".txt" 
	outputFile = open(outputFileName, "w")

	# list to keep track of edges already added in graph
	adjList = dict()
	# list to keep track if a node has been connected or not
	marked = []
	# maxmimum weight any edge can have in the graph
	maxWeight = int(n)*(int(n)-1)

	# initalize output file
	outputFile.write(n+ "\n");
	outputFile.write(e+ "\n");

	#for each node add an empty list 
	for node in range(0,int(n)):
		neighbours = []
		adjList[node] = neighbours

	#print(adjList)
	i = 0
	# if it is the first edge to be added
	flagFirst = True
	# To connect the graph fully add n-1 edges such that each edge connect the connected 
	#component to a not marked node

	while i <int(n)-1:
		#print(node)
		node1 = random.randint(0,int(n)-1)
		node2 = random.randint(0,int(n)-1)
		weight = random.randint(0, maxWeight)

		if flagFirst: #initally both the nodes will be unmarked
			marked.append(node1)
			marked.append(node2)

			adjList[node1].append(node2)
		
			adjList[node2].append(node1)
	
			outputFile.write(str(node1) + " " + str(node2) + " " + str(weight) + "\n")
			i += 1
			flagFirst = False

		# After the first edge is added add edges only from the nodes which are already marked to 
		# the nodes which are not
		else:	
			if(node1 != node2):
				if (node1 not in marked) and (node2 in marked):
					marked.append(node1)

					adjList[node1].append(node2)
		
					adjList[node2].append(node1)
	
					outputFile.write(str(node1) + " " + str(node2) + " " + str(weight) + "\n")
					i += 1
				elif (node2 not in marked) and (node1 in marked):
					marked.append(node2)

					adjList[node1].append(node2)
		
					adjList[node2].append(node1)

					outputFile.write(str(node1) + " " + str(node2) + " " + str(weight) + "\n")
					i += 1
		
	remainingEdges = int(e)-int(n)+1

	i = 0
	# for the remaining edges just add an edge if the same edge has not been added before
	while i < remainingEdges:
		node1 = random.randint(0,int(n)-1)
		node2 = random.randint(0,int(n)-1)
		weight = random.randint(0, maxWeight)

		if(node1 != node2):
			if node2 not in adjList[node1]:
				adjList[node1].append(node2)
		
				adjList[node2].append(node1)

				outputFile.write(str(node1) + " " + str(node2) + " " + str(weight) + "\n")

				i += 1

	print(adjList)

	outputFile.close()

