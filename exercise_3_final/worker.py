from multiprocessing.managers import BaseManager
from multiprocessing import Process, Lock, Array, cpu_count
import time
import sys


class QueueManager(BaseManager): 
    pass


QueueManager.register('in_queue')
QueueManager.register('out_queue')
m = QueueManager(address=('localhost', 8080), authkey=b'blah')
m.connect()
in_queue = m.in_queue()
out_queue = m.out_queue()


def multiplay(process_work, matrix_data, part_of_vec, lock, final_values):
    rows_number = len(matrix_data)
    columns_number = len(matrix_data[0])
    local_values = [0 * x for x in range(rows_number)]
    for i in range(process_work[0], process_work[1]):
        a = int(i / columns_number)
        b = int(i % columns_number)
        local_values[a] += matrix_data[a][b] * part_of_vec[b][0]
    lock.acquire()
    for i in range(len(local_values)):
        final_values[i] += local_values[i]
    lock.release()


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
    lock = Lock()
    processes = []
    cpu_number = int(sys.argv[1]) if  len(sys.argv) >= 2 else cpu_count()
    print(cpu_number)
    time.sleep(1)
    in_queue.put("init")

    while True:
        data = in_queue.get()
        if type(data) is tuple:
            final_values = Array('d', range(len(data[1])))
            for i in range(len(data[1])):
                final_values[i] = 0
            division = divide_work(cpu_number, len(data[1]) * len(data[1][0]))
            for num in range(cpu_number):
                process_work = (division[num], division[num + 1])
                process = Process(target =multiplay, args=(process_work, data[1], data[2], lock, final_values))
                processes.append(process)
                process.start()        
            for process in processes:
                process.join()
            out_queue.put((data[0], final_values[:]))


if __name__== "__main__":
  main()