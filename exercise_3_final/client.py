import sys
from multiprocessing.managers import BaseManager
import time

class QueueManager(BaseManager): 
    pass

QueueManager.register('in_queue')
QueueManager.register('out_queue')

m = QueueManager(address=('localhost', 8080), authkey=b'blah')
m.connect()
in_queue = m.in_queue()
out_queue = m.out_queue()


def read_file(file_name):
    f = open(file_name,"r")
    row_size = int(f.readline())
    column_size = int(f.readline())
    values = f.readlines()
    f.close()   
    matrix = []
    tempRow = []
    i = 0

    for value in values:
        tempRow.append(float(value))
        i += 1
        if i % column_size == 0:
            matrix.append(tempRow)
            tempRow = []

    if len(matrix) != row_size:
        print("Error during parsing file")
        return None
    
    if len(matrix[0]) != column_size:
        print("Error during parsing file")
        return None    

    return matrix


def divide_work(number, data_number):
    division = []
    step = int(data_number/number)
    last_step = data_number % number
    for i in range(0, number + 1):
        division.append(i * step)
    if (last_step != 0):
        division[len(division) - 1] += last_step
    return division




def main():
    tasks_number = int(sys.argv[1]) if  len(sys.argv) >= 2 else 1

    matrix = read_file("A.dat")
    vector = read_file("X.dat")


    start = time.time()
    division = divide_work(tasks_number, len(matrix))
    for i in range (0, tasks_number):
        in_queue.put((i, matrix[division[i]:division[i+1]], vector))

    results_to_parse = [0 * x for x in range(tasks_number)]
    i = 0

    out_queue.put("init")
    time.sleep(1)

    while i != tasks_number:
        result = out_queue.get()
        if type(result) is tuple:
           results_to_parse[result[0]] = result[1]
           i += 1 
    
    final_result = []
    for result in results_to_parse:
        final_result.extend(result)
        
    end = time.time()
    print(final_result)
    print("Czas wykonania: ",  str(end - start - 1))


if __name__== "__main__":
  main()