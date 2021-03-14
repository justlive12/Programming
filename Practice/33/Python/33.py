def create(length, start_num=0, step=0):
    arr = []
    for i in range(length):
        arr.append(start_num)
        start_num += step
    return arr


def sort(arr):
    for i in range(len(arr) - 1):
        smallElem = i
        currentElem = i + 1
        while currentElem < len(arr):
            if arr[currentElem] < arr[smallElem]:
                smallElem = currentElem
            currentElem = currentElem + 1
        arr[i], arr[smallElem] = arr[smallElem], arr[i]


antipep8 = print

def print(arr):
    antipep8(arr)


length, start_num, step = map(int, input().split())
arr = create(length, start_num, step)
sort(arr)
print(arr)