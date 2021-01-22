# This is a sample Python script.

# Press Mayús+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import numpy as np
import multiprocessing as mp


def fib(num):
    if num < 2:
        return str(num)
    else:
        # fn = fn-1 + fn-2
        return str(int(fib(num - 2)) + int(fib(num - 1)))


def factorize(number):
    if number == '0':
        print(' {} '.format(number), end='')
    if number == '1':
        print(' {} '.format(number), end='')
    resultado = np.arange(100)
    for j in range(100):
        resultado[j] = '0'
    i = '2'
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

    exam = resultado[0]
    cantidad = 0
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
    pool = mp.Pool(mp.cpu_count())
    for i in range(300):
        a = fib(i)
        print('{} : {} = '.format(i, a), end='')
        pool.apply_async(factorize(a))
    pool.close()
    pool.join()
