import unittest
from itertools import combinations

class TestCalc(unittest.TestCase):

    # calculate sum of elements

    def test_SumOfElements(self):
        result1 = sum([10,5,4,3,2])
        self.assertEqual(result1,24) # test == true

        result2 = sum([10,18,4,6,2])
        self.assertEqual(result2,40) # should return false

    # finding ideal groups according to vacancy created inside

    def test_MakeCombinations(self):
        sampleList = []
        vacancy = 10
        comb = combinations([10,6,4,3,7], 2)
        for i in comb:
            if(sum(i) <= vacancy):
                sampleList.append(i)
        self.assertEqual(sampleList, [(6, 4), (6, 3), (4, 3), (3, 7)]) # should return true

    # finding the Ideal Combination to get inside restaurant

    def test_IdealCombination(self):
        sampleList2 = [(6, 4), (6, 3), (4, 3), (3, 7)]
        sampleList3 = []

        for i in sampleList2:
            sampleList3.append(max(i)); 
    
        idx = sampleList3.index(min(sampleList3))
        result3 = sampleList2[idx]
        self.assertEqual(result3, (4,3)) # should return true
        # self.assertEqual(result3, (5,3)) # should return false 

    # sorting the elements
    
    def test_bubble(self):
        data = [10 ,7 ,4 ,3 ,6]
        
        data.sort()
        result4 = data
        self.assertEqual(result4, [3, 4, 6, 7, 10]) # should return true


if __name__=='__main__':
    unittest.main()
