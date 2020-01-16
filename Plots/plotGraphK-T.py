import sys
import matplotlib.pyplot as plt 

# if sufficient command line arguments not passed
if len(sys.argv) < 2: 
    print("Usage: python plotGraphK-T.py <Time taken file> <name of the plot>")
    exit()
else:   

     # x-axis values 
    K = [] 
    # y-axis values 
    T = [] 

    #For 2-ary heap: 1138 microseconds

    inputFile = open(sys.argv[1], "r")

    for line in inputFile:
        indexK = line.find("For")
        indexDash = line.find("-")
        K.append(line[indexK + 4: indexDash])


        indexColon = line.find(":")
        indexms = line.find("micro")
        T.append(line[indexColon+2: indexms-1])

    for i in range(0,len(K)):
        print(K[i], T[i])
    
    #x1 = K[0]
    #x2 = K[len(K)-1]
    #set_xlim(x1, x2)
    #plt.ylim(T[0], T[len(K)-1])
    
    # plotting points as a scatter plot 
    plt.scatter(K, T, label= "points", color= "black",  marker= "*", s=30) 
    
    # plotting the line 1 points  
    plt.plot(K, T, label = "line")

    # x-axis label 
    plt.xlabel('K of the K-ary heap used') 
    # frequency label 
    plt.ylabel('Time taken in microseconds') 

    # plot title 
    if(len(sys.argv) >= 3):
        plt.title(sys.argv[2])
    else:
        plt.title('K-ary vs Time taken plot') 
    # showing legend 
    plt.legend() 
  
    # function to show the plot 
    plt.show() 
