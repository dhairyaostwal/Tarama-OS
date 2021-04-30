from itertools import combinations

def IdealCombination(data):
    sampleList = []

    for i in data:
        sampleList.append(max(i))
    print(min(sampleList))

def MakeCombinations(data,v):
    
    sampleList = []

    comb = combinations(data,2)
    for i in comb:
        if(sum(i)<=v):
            sampleList.append(i)
    for j in sampleList:
        print(j)

    IdealCombination(sampleList)

data1 = [10,6,4,3,7]
vacancy = 10

MakeCombinations(data1, vacancy)
# IdealCombination([(3,2),(4,6)])
data1.sort()
print(data1)