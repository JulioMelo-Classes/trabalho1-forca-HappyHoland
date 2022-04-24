# receives one file and breaks it into input an output to be teste
import sys, os, shutil

if len(sys.argv) == 1:
    sys.exit(-1)

#the base file with ';' separing input/output of each test
file = sys.argv[1]
#the path where the in and expected files will be saved
testPath = sys.argv[2]
inputPath = '{}/data_in'.format(testPath)
outputPath = '{}/data_expected'.format(testPath)

try: 
    os.mkdir(inputPath)
except FileExistsError: #already there
    shutil.rmtree(inputPath)
    os.mkdir(inputPath)

try: 
    os.mkdir(outputPath)
except FileExistsError: #already there
    shutil.rmtree(outputPath)
    os.mkdir(outputPath)

with open(file) as f:
    lines = f.readlines()

readingInput = True
readingOutput = False
input = ''
output = ''
testCount = 1
for l in lines:
    if not l.startswith(';') and readingInput :
        input += l
    elif l.startswith(';') and readingInput :
        readingInput = False
        readingOutput = True
    elif not l.startswith(';') and readingOutput :
        output += l
    elif l.startswith(';') and readingOutput :
        inputFile = open('{}/in{}.txt'.format(inputPath, testCount), 'w')
        inputFile.write(input[:len(input)-1])
        inputFile.close()
        outputFile = open('{}/in{}_OUT.txt'.format(outputPath, testCount), 'w')
        outputFile.write(output[:len(output)-1])
        outputFile.close()

        testCount = testCount + 1
        input = ''
        output = ''
        readingInput = True
        readingOutput = False
    


