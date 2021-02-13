import random
import threading

import numpy
import time

import psutil as psutil

vector1 = []
vector2 = []
vectorSize = 0
result = 0
xp = 0
threadNumber = psutil.cpu_count()
results = [0 for _ in range(0, threadNumber)]

class myThread(threading.Thread):
    s = 0
    end = 0
    sign = 0

    def __init__(self, s, end, sign):
        threading.Thread.__init__(self)
        self.s = s
        self.end = end
        self.sign = sign

    def run(self):
        re = 0
        for i in range(self.s, self.end):
            re += vector1[i] * vector2[i]
        results[self.sign] = re


        
def randomGenerate():
    global xp
    xp=((xp>>3)+4)
    return xp<<2


def pythonInSize():
    global vectorSize
    print("Please input the size:")
    while (True):
        in1 = input()
        try:
            vectorSize = int(in1)
        except ValueError:
            print("The input " + in1 + " is not valid! Please try again!")
        if (len(in1) >= 10):
            print("The input size is too large!")
        else:
            break
        print("Please input the size again:")


def initiate():
    global vector1, vector2, xp
    vector1 = [0 for _ in range(0, vectorSize)]
    vector2 = [0 for _ in range(0, vectorSize)]
    xp = int(random.uniform(-1 * 0x7fffffff, 0x7fffffff))

def pythonInElements(sign):
    if sign == 1:
        for i in range(0, vectorSize):
            vector1[i] = 1
    else:
        for i in range(0, vectorSize):
            vector2[i] = 1


def singleThreadMethod():
    global result
    t1 = time.process_time()
    for i in range(0, vectorSize):
        result += vector1[i] * vector2[i]
    print(result)
    t2 = time.process_time()
    print((t2 - t1), "s")


def numpyMethod():
    t1 = time.process_time()
    print(numpy.dot(vector1, vector2))
    t2 = time.process_time()
    print((t2 - t1), "s")


def subMutiply(start, end, sign):
    re = 0
    for i in range(start, end):
        re += vector1[i] * vector2[i]
    results[sign] = re


def mutipleThreadMethod():
    t1 = time.process_time()
    each =int(vectorSize / threadNumber)
    start = 0
    end = each
    threadpool = []
    for i in range(0, threadNumber):
        if i == threadNumber - 1:
            end = vectorSize
        tt = myThread(start, end, i)
        tt.start()
        threadpool.append(tt)

        start = end
        end += each

    for i in range(0, threadNumber):
        threadpool[i].join()
    re = 0
    for i in range(0, threadNumber):
        re += results[i]

    print(re)
    t2 = time.process_time()
    print((t2 - t1), "s")


if __name__ == '__main__':
    pythonInSize()
    initiate()
    t1 = time.process_time()
    pythonInElements(1)
    pythonInElements(2)
    t2 = time.process_time()
    print("Data IO Time:", (t2 - t1), "s")
    singleThreadMethod()
    numpyMethod()
    mutipleThreadMethod()