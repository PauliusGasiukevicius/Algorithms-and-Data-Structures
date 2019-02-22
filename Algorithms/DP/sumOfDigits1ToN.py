def digitsSum(n):
    return sum(int(x) for x in str(n))

def solve(n):
    if n < 10 : return n*(n+1)//2
    d = len(str(n))-1
    ways = 45
    for i in range(1,d):
        ways = 10*ways + 45*10**i
    msd = n//10**d
    return msd*ways + solve(msd-1)*10**d + msd*(1+n%10**d) + solve(n%10**d)

n = int(input())
print(solve(n))
