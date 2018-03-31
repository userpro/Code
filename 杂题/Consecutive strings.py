'''
You are given an array strarr of strings and an integer k. 
Your task is to return the first longest string consisting 
of k consecutive strings taken in the array.

#Example: 
longest_consec(
    ["zone", "abigail", "theta", "form", "libe", "zas", "theta", "abigail"], 
    2
    ) --> "abigailtheta"

n being the length of the string array, 
if n = 0 or k > n or k <= 0 return "".
'''
def longest_consec(strarr, k):
    if k <= 0 or k > len(strarr) or not strarr: return ""
    a = list(map(lambda x:len(x), strarr))
    b = len(a) - k + 1
    c = [0] * b
    for i in range(b):
        for j in range(i, i+k):
            c[i] += a[j]

    d = c.index(max(c))
    e = ''
    for i in range(d, d+k):
        e += strarr[i]
    
    return e


print(longest_consec(["zone", "abigail", "theta", "form", "libe", "zas"], 2) == "abigailtheta")
print(longest_consec(["ejjjjmmtthh", "zxxuueeg", "aanlljrrrxx", "dqqqaaabbb", "oocccffuucccjjjkkkjyyyeehh"], 1) == "oocccffuucccjjjkkkjyyyeehh")
print(longest_consec([], 3) == "")
print(longest_consec(["itvayloxrp","wkppqsztdkmvcuwvereiupccauycnjutlv","vweqilsfytihvrzlaodfixoyxvyuyvgpck"], 2) == "wkppqsztdkmvcuwvereiupccauycnjutlvvweqilsfytihvrzlaodfixoyxvyuyvgpck")
print(longest_consec(["wlwsasphmxx","owiaxujylentrklctozmymu","wpgozvxxiu"], 2) == "wlwsasphmxxowiaxujylentrklctozmymu")
print(longest_consec(["zone", "abigail", "theta", "form", "libe", "zas"], -2) == "")
print(longest_consec(["it","wkppv","ixoyx", "3452", "zzzzzzzzzzzz"], 3) == "ixoyx3452zzzzzzzzzzzz")
print(longest_consec(["it","wkppv","ixoyx", "3452", "zzzzzzzzzzzz"], 15) == "")
print(longest_consec(["it","wkppv","ixoyx", "3452", "zzzzzzzzzzzz"], 0) == "")