# n = int(input())
# if n == 0:
#     print(0)
# arr = list(map(int, input().split()))
# if n == 1:
#     print(arr[0])
# arr.sort()
# if len(arr) % 2 == 0:
#     print(arr[n//2 - 1])
# else:
#     print(arr[n//2])

#####################2
# def intToRoman(num: int) -> str:
#     ans = ""
    
#     ans += (num//1000)*'M'
#     num %= 1000
    
#     if num // 100 == 9:
#         ans += 'CM'
#         num %= 900
#     elif num // 100 == 4:
#         ans += 'CD'
#         num %= 400
#     else:
#         ans += (num//500) * 'D'
#         num %= 500
    
#     ans += (num//100) * 'C'
#     num %= 100
    
#     if num // 10 == 9:
#         ans += 'XC'
#         num %= 90
#     elif num // 10 == 4:
#         ans += 'XL'
#         num %= 40
#     else:
#         ans += (num//50) * 'L'
#         num %= 50

#     ans += (num//10) * 'X'
#     num %= 10

#     if num  == 9:
#         ans += 'IX'
#         num = 0
#     elif num == 4:
#         ans += 'IV'
#         num = 0
#     else:
#         ans += (num//5) * 'V'
#         num %= 5 
#     ans += num * 'I' 
#     return ans
# num = int(input())
# print(intToRoman(num))

###################################3
def maxSubArray(nums):
    if not nums:
        return 0; 
    ans = -float('inf')
    cur_sum = 0
    for i in range(len(nums)):
        if (cur_sum < 0):
            cur_sum = nums[i];
        else:
            cur_sum += nums[i];
        ans = max(cur_sum, ans);
    return ans; 
nums = list(map(int, input().split(', ')))
print(maxSubArray(nums))