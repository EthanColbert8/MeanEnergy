# -*- coding: utf-8 -*-
"""
Created on Tue Mar 15 23:40:40 2022

@author: Ethan
"""

import subprocess
import csv

def stringsToFloats(rawList):
    convertedList = []
    for candidate in rawList:
        try:
            convertedList.append(float(candidate))
        except:
            pass
    return convertedList

temps = [10.0, 100.0, 200.0, 300.0, 1000.0, 2000.0, 3000.0, 4000.0, 10000.0, 20000.0]
freqs = [1.0, 2.0, 3.0, 100.0, 200.0, 300.0, 400.0, 1000.0, 2000.0]
resultList = []

for freq in freqs:
    for temp in temps:
        rawOutput = subprocess.check_output(["mpirun", "-np", "7", "-H",
                                    "localhost,knights@n2,knights@n3,knights@n5,knights@n6,knights@n7,knights@n9",
                                    "energy", str(freq), str(temp), "2000000000"])
        output = stringsToFloats(rawOutput.split())
        resultList.append([temp, freq, output[0]])

outFile = open("TempDependence.csv", 'w')
writer = csv.writer(outFile)

for rowData in resultList:
    writer.writerow(rowData)

outFile.close()

print("Finsihed run.\n")