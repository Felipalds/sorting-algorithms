def flip(arr, k: int) -> None:
    left = 0
    while left < k:
        arr[left], arr[k] = arr[k], arr[left]
        k -= 1
        left += 1

def max_index(arr, k: int) -> int:
    index = 0
    for i in range(k):
        if arr[i] > arr[index]:
            index = i
    return index

def pancake_sort(arr) -> None:
    n = len(arr)
    while n > 1:
        maxdex = max_index(arr, n)
        if maxdex != n - 1:
            if maxdex != 0:
                flip(arr, maxdex)
            flip(arr, n - 1)
        n -= 1

arreglo = [15, 8, 9, 1, 78, 30, 69, 4, 10]
pancake_sort(arreglo)
print(arreglo)
