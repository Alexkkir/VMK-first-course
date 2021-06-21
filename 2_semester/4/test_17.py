from random import randint as rand

MAX_INT = 2 ** 32 - 1
two = 2 ** 32
ten = 10 ** 9

# print('%5d' % 123)
for i in range(20):
    # w0, w1, w2 = [rand(0, MAX_INT) for i in range(3)]
    w0, w1, w2 = [0, 1, 0]

    fact_res = w2 * two * two + w1 * two + w0

    my_res = int(f"{w2 // ten}{w2 % ten + w1 // ten}{w1 % ten + w0 // ten}{w0 % ten}")
    print(fact_res, my_res)
