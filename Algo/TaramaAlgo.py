from itertools import combinations


def unique(list1): 
    list_set = set(list1) 
    unique_list = (list(list_set)) 
    return unique_list

def mini(arr):
    for i in range(0, len(arr)):
        if(arr[i] != 0):
            return arr[i]

def minii(arr):
    for i in range(0, len(arr)):
        if(arr[i] != -1):
            return arr[i]

def bubble(arr, b):
    n = len(arr) 

    for i in range(n-1): 
        for j in range(0, n-i-1): 
            if arr[j] > arr[j+1] : 
                arr[j], arr[j+1] = arr[j+1], arr[j] 
                b[j], b[j+1] = b[j+1], b[j] 

insideTarama = [10, 9, 9, 1, 1]
inqueue = [10, 4, 9, 5, 2]
inqueue1 = []
for i in inqueue:
    inqueue1.append(i)
capacity = 30
replacedpos = []
l = []
l1 = []
insert = []
currentstatus = []
sumele = []
waiting = []
for i in range(len(inqueue)):
    waiting.append(0)


def schedulecheck():

    waitingtime = 0
    insideTarama.sort()
    bubble(inqueue, waiting)
    for i in range(0, len(insideTarama)):
        currentstatus.insert(i, insideTarama[i])
    
    print("inside Tarama: ", insideTarama)
    print("inside Queue: ", inqueue)
    print("Current status in restaurant: ", currentstatus)
    Vacancy = capacity - sum(insideTarama)
    print("Initial Vacancy: ", Vacancy)
    
    k1 = 0
    while(k1 < len(inqueue)):
        bubble(insideTarama, currentstatus)
        if(len(inqueue) == 0):
            break     

        temp = 0
        for i in range(0, len(inqueue)):
            if(Vacancy < minii(inqueue) or Vacancy == 0):
                temp = mini(currentstatus)
                waitingtime += temp
                for j in range(0, len(insideTarama)):
                    if(currentstatus[j] >= temp):
                        currentstatus[j] -= temp
                    else:
                        currentstatus[j] = 0
                print(currentstatus)
                for j in range(0, len(currentstatus)):
                    if(currentstatus[j] == 0):
                        print("V: ", Vacancy, " + ", insideTarama[j])
                        Vacancy += insideTarama[j]
                        insideTarama[j] = 0
                        replacedpos.append(j)
                print("Total Vacancy: ", Vacancy)
            else:
                break
        for i in range(len(inqueue), 0, -1):
            comb = combinations(inqueue, i)
            for j in comb:
                if(sum(j) <= Vacancy):
                    l1.append(j)
                    sumele.append(sum(j))

        bubble(sumele, l1)
        print("Waiting time for foll: ", waitingtime)
        print("Inserted Are: ", (list(l1[len(l1) - 1])))
        Vacancy -= sumele[len(sumele) - 1]
        insideTarama.extend(list(l1[len(l1) - 1]))
        currentstatus.extend(list(l1[len(l1) - 1]))

        for i in range(0, len(unique(replacedpos))):
            unique(replacedpos)[i] -= i
            insideTarama.pop(unique(replacedpos)[i] - i)
            currentstatus.pop(unique(replacedpos)[i] - i)

        

        print(l1[-1])

        for i in range(len(l1[-1])):
            print(inqueue1)
            waiting[inqueue1.index(l1[-1][i])] = waitingtime
            print("&&&&", inqueue1.index(l1[-1][i]))
            inqueue.pop(inqueue.index(l1[-1][i]))
            inqueue1[inqueue1.index(l1[-1][i])] = 0
        print("waiting", waiting)

        print("New Vacancy: ", Vacancy)
        print("Insides Tarama Status: ", insideTarama)
        print("Current Status: ", currentstatus)
        print("Inqueue: ", inqueue)
        bubble(insideTarama, currentstatus)

        

        replacedpos.clear()
        l1.clear()
        sumele.clear()
    # while 0 in waiting: waiting.remove(0)
    print(waiting)

schedulecheck()
