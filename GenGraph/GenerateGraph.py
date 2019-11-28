import random
import sys

if len(sys.argv) != 3:
	print("Usage: python GenerateGraph.py <number of nodes> <number of edges>")
	exit()
else:
	n = sys.argv[1]
	e = sys.argv[2]
	outputFileName = "graph_"+str(n)+"_"+str(e)+".txt"
	outputFile = open(outputFileName, "w")

	adjList = dict()
	marked = []
	maxWeight = int(n)*(int(n)-1)

	outputFile.write("n="+n+", e="+e+"\n")

	for node in range(0,int(n)):
		neighbours = []
		adjList[node] = neighbours

	#print(adjList)
	i = 0
	flagFirst = True
	while i <int(n)-1:
		#print(node)
		node1 = random.randint(0,int(n)-1)
		node2 = random.randint(0,int(n)-1)
		weight = random.randint(0, maxWeight)

		if flagFirst:
			marked.append(node1)
			marked.append(node2)

			adjList[node1].append(node2)
		
			adjList[node2].append(node1)
	
			outputFile.write(str(node1) + "," + str(node2) + "," + str(weight) + "\n")
			i += 1
			flagFirst = False

		else:
			if(node1 != node2):
				if (node1 not in marked) and (node2 in marked):
					marked.append(node1)

					adjList[node1].append(node2)
		
					adjList[node2].append(node1)
	
					outputFile.write(str(node1) + "," + str(node2) + "," + str(weight) + "\n")
					i += 1
				elif (node2 not in marked) and (node1 in marked):
					marked.append(node2)

					adjList[node1].append(node2)
		
					adjList[node2].append(node1)

					outputFile.write(str(node1) + "," + str(node2) + "," + str(weight) + "\n")
					i += 1
		
	remainingEdges = int(e)-int(n)+1

	i = 0
	while i < remainingEdges:
		node1 = random.randint(0,int(n)-1)
		node2 = random.randint(0,int(n)-1)
		weight = random.randint(0, maxWeight)

		if(node1 != node2):
			if node2 not in adjList[node1]:
				adjList[node1].append(node2)
		
				adjList[node2].append(node1)

				outputFile.write(str(node1) + "," + str(node2) + "," + str(weight) + "\n")

				i += 1

	print(adjList)

	outputFile.close()

