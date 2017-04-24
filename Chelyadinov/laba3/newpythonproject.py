def delete_versh(graph):
    print "Vvedite vershinu ot ",0, " do ", len(graph)-1
    versh=int(input())
    if versh>=len(graph) or versh <0:
        return False
    global check
    check=[]
    check_versh(graph,versh)
    #print check
    delete=list(set(check)^set(range(len(graph))))
    #print delete
    if delete!=[]:
        print "Udaleni vershini: ",
        for i in delete:
            graph[i]=[]
            print i," ",
        print
    else:
        print "Nichego ne udaleno"
    print_graph(graph)
    return True


def print_graph(graph):
    print graph
    for i in graph:
        for j in range(len(graph)):
            print int(j in i)," ",
        print 
    
def check_versh(graph,versh):
    check.append(versh)
    for j in graph[versh]:
        if j not in check:
            check_versh(graph,j)
          

   
j=0
graph=[]
try:
    file=open("input.txt","r")
    for line in file.read().split("\n"):
        graph.append([])
        p=0
        for i in line.split(" "):
            if int(i)>0:
                graph[j].append(int(p))
            p=p+1    
        j=j+1        
    print_graph(graph)
    while not delete_versh(graph):
        print "Vvedena ne vernaya vershina!!\n"
    file.close()
except IOError:
    print "File not found"
    
        
        
