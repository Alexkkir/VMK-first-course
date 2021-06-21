n = int(input())
orders = [[x for x in input().split()] for i in range(n)]

def intersection_max(orders):
    times = []
    for order in orders:
        startTime, endTime = order
        times.append((startTime, 'start'))
        times.append((endTime, 'end'))
    times.sort()

    count = 0
    maxCount = 0
    for time in times:
        if time[1] == 'start':
            count += 1    # increment on arrival/start
        elif time[1] == 'end':
            count -= 1    # decrement on departure/end
        maxCount = max(count, maxCount)  # maintain maximum
    return maxCount

print(intersection_max(orders))
