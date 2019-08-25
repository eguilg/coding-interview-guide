from collections import defaultdict

n, m = map(int, input().split())
freq_dict = defaultdict(int)
nums = list(map(int, input().split()))

for num in nums:
    freq_dict[num] += 1
nums = [num for num in nums if freq_dict[num] <= m]
print(' '.join(list(map(str, nums))))