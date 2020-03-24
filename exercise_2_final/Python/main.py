import threading
import time
import math
import sys
from multiprocessing import Pool

threadLock = threading.Lock()

def read_file(file_name):
    f = open(file_name,"r")
    lines = f.readlines()
    f.close()   
    matrix = []
    i = 0
    rows = 0
    columns = 0
    for line in lines:
        if i == 0:
            rows = int(line)
        elif i == 1:
            columns = int(line)
        else:
            temp = line.split()
            if len(temp) != columns:
                print("Error during parsing file")                
                return None
            tempDouble = [float(val) for val in temp]
            matrix.append(tempDouble)            
        i += 1

    if len(matrix) != rows:
        print("Error during parsing file")
        return None
    
    if len(matrix[0]) != columns:
        print("Error during parsing file")
        return None
    
    return matrix

def row_multiply_column(matrix_A, matrix_B, row_index, column_index):
    value = 0.0
    for i in range (0, len(matrix_A[row_index])):
        value += matrix_A[row_index][i] * matrix_B[i][column_index]  
    return value

def multiply_thread(matrix_A, matrix_B, data, results):
    local_results = []
    for pair in data:
        value = row_multiply_column(matrix_A, matrix_B, pair[0], pair[1])
        local_results.append([pair[0], pair[1], value])        
    threadLock.acquire()
    for result in local_results:
        results[result[0]][result[1]] = result[2]
    threadLock.release()

def multiply_matrix(matrix_A, matrix_B, threads_number):
    rows_A = len(matrix_A)
    columns_A = len(matrix_A[0])
    rows_B = len(matrix_B)    
    columns_B = len(matrix_B[0])
    if columns_A != rows_B:
        return None
    results = [[0] * columns_B for i in range(rows_A)] 
    pairs = []
    for i in range (0, rows_A):
        for j in range (0, columns_B):
            pairs.append([i, j])
    local_threads_number = threads_number if threads_number <= len(pairs) else len(pairs)
    step = int(len(pairs) / local_threads_number)
    last_step = len(pairs) % local_threads_number
    last_step_offset = len(pairs) - last_step - 1
    thread_data = []
    for i in range(0, local_threads_number):
        thread_data.append([])
        for j in range(0, step):
            thread_data[i].append(pairs[i * step + j])
    
    for i in range(1, last_step + 1):
        thread_data[(i - 1) % local_threads_number].append(pairs[last_step_offset + i])    

    threads = []
    for i in range(0, local_threads_number):
        thread = threading.Thread(target=multiply_thread, args=(matrix_A, matrix_B, thread_data[i], results,))
        threads.append(thread)
        thread.start()

    for t in threads:
        t.join()
    
    return results

def frobenius_thread(flat_list, data, result):
    local_result = 0.0
    for i in range(data[0], data[1]): 
        local_result += flat_list[i] ** 2    
    threadLock.acquire()
    result[0] += local_result
    threadLock.release()

def calculate_frobenius(matrix, threads_number):
    flat_list = []
    for sublist in matrix:
        for item in sublist:
            flat_list.append(item)    
    elements_number = len(matrix) * len(matrix[0])
    thread_data = []
    result = [0]
    local_threads_number = threads_number if threads_number <= elements_number else elements_number
    step = int(elements_number / local_threads_number)
    last_step = elements_number % local_threads_number
    for i in range (0, local_threads_number * step, step):
        thread_data.append([i, i + step])
    thread_data[local_threads_number - 1][1] = thread_data[local_threads_number - 1][1] + last_step
    threads = []
    for i in range(0, local_threads_number):
        thread = threading.Thread(target=frobenius_thread, args=(flat_list, thread_data[i], result,))
        threads.append(thread)
        thread.start()

    for t in threads:
        t.join()
    
    return math.sqrt(result[0])


       

def main():
    thread_number = int(sys.argv[1]) if  len(sys.argv) >= 2 else 1
    if thread_number < 1:
        thread_number = 1
    matrix_A = read_file("A.txt")
    matrix_B = read_file("B.txt")

    if matrix_A is None:
        print("Error during reading file A.txt")

    if matrix_B is None:
        print("Error during reading file B.txt")

    start = time.time()
    matrix_C = multiply_matrix(matrix_A, matrix_B, thread_number)
    end = time.time()
    if matrix_C is None:
        print("Matrixes have incorrect size - multiplaying impossible.")
        return
    print("Result of multiplaying: \n")
    for res in matrix_C:
        for r in res:
            print(str(r) + " ", end='')
        print("\n")
    print("Multiplication time: " + str(end - start))

    start = time.time()
    result = calculate_frobenius(matrix_C, thread_number)
    end = time.time()
    print("Frobenius norm = " + str(result))
    print("Frobenius norm calculation time: " + str(end - start))
    print("Number of threads: " + str(thread_number))



if __name__== "__main__":
  main()