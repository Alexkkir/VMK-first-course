l, n = [int(x) for x in input().split()]
orders = []
for i in range(n):
    orders.append(int(input()))

def intersection_max(orders):
    times = []
    for order in orders:
        startTime, endTime = order - l, order + l
        times.append((startTime, 'start'))
        times.append((endTime, 'end'))
    times.sort(key = lambda x: x[1])
    times.sort()

    # print(times)

    count = 0
    max_count = 0
    i_now = 0; i = 0
    while i < len(times):
        ends = 0
        starts = 0
        while i < len(times) and times[i_now] == times[i]:
            if times[i][1] == 'start':
                starts += 1
            else:
                ends += 1
            i += 1
        i_now = i
        count += starts
        max_count = max(count, max_count)
        count -= ends
    return max_count
    # for time in times:
    #     if time[1] == 'start':
    #         count += 1    # increment on arrival/start
    #     elif time[1] == 'end':
    #         count -= 1    # decrement on departure/end
    #     maxCount = max(count, maxCount)  # maintain maximum
    # return maxCount


print(intersection_max(orders))
 # python C:\Users\1\Documents\EVM\algorithms_mail\exam_1\2.py
