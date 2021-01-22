# Numpy array import
import numpy as np

# Import python parallel processing
import multiprocessing as mp

# Tethod that calculates fibonacci with recursion 
def fib(num):    
    if num < 2:
        return str(num)
    else:
        # Returns the sum of the two previous numbers
        return str(int(fib(num - 2)) + int(fib(num - 1)))

# Factorize the number
def factorize(number,d):    
    print('{} : {} = '.format(d, number), end='')
    if number == '0':
        print(' {} '.format(number), end='')
    if number == '1':
        print(' {} '.format(number), end='')
    # Result array
    resultado = np.arange(100)
    for j in range(100):
        resultado[j] = '0'
    # Instance number
    i = '2'
    # Posision number
    pos = 0
    while True:
        if str(int(number) % int(i)) == '0':
            number = str(int(number) // int(i))
            resultado[pos] = i
            pos = pos + 1
        else:
            if i == '2':
                i = '3'
            else:
                i = str(int(i) + 2)
        if (int(i) * int(i)) > int(number) + 1:
            if number != '1':
                resultado[pos] = number
            break
    # Aux number
    exam = resultado[0]
    cantidad = 0
    # Transform resutlado a string and print the result
    for i in range(100):
        if exam == resultado[i]:
            cantidad = cantidad + 1
        else:
            if cantidad == 1:
                print(' {} '.format(exam), end='')
            else:
                print(' {} ^ {}'.format(exam, cantidad), end='')
            exam = resultado[i]
            cantidad = 1
            if resultado[i] == 0:
                break
            print(' x', end='')
    print()


if __name__ == '__main__':
    #freeze_support()
    # Create a pool whit the max core
    pool = mp.Pool(mp.cpu_count())
    # Create all instance fib
    for i in range(300):
        # Calculate a fibonacci number and factorize whit parallelization
        pool.apply_async(factorize(fib(i),i))
    
