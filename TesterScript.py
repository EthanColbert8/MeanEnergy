# -*- coding: utf-8 -*-
"""
Created on Thu Mar 10 15:22:21 2022

@author: Ethan
"""

import subprocess
#import math

testCaseFile = open("test_cases.txt", 'r')
testList = [x.strip() for x in testCaseFile.readlines()]
testCaseFile.close()

numTests = len(testList)
print("There are", numTests, "test cases.\n")

testCases = []
for line in testList:
    testCases.append(line.split())

for test in range(0, numTests):
    processResult = subprocess.run(["energy_sequential", testCases[test][0],
                                    testCases[test][1], testCases[test][2]],
                                   capture_output=True, text=True)
    #print(processResult.stdout)
    obtainedResult = float(processResult.stdout.split()[-1])
    expectedResult = float(testCases[test][3])
    
    comparison = (obtainedResult - expectedResult) / expectedResult
    if comparison < 0.05:
        print("Test", test+1, "passed!")
    else:
        print("Oops! Test", test, "failed.")
    print("Obtained result: ", obtainedResult, "\nExpected result:", expectedResult, "\n")
