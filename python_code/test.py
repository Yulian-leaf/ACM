def solve(n, ranges):
    result = []
    used = [False] * (n + 1)
    def pan(index):
        if index == n:
            return True
        for num in range(1, n + 1):
            if used[num] or not (ranges[index][0] <= num <= ranges[index][1]):
                continue
            used[num] = True
            result.append(num)
            if pan(index + 1):
                return True
            used[num] = False
            result.pop()
        return False
    
    if pan(0):
        ll=[0]*(n+1)
        # print(result,ranges,n)
        for i in range(n):
            # print(i,end=' ')
        # print(ranges[2][2])
            ll[ranges[i][2]]=result[i]
        for i in range(n):
            print(ll[i],end=' ')
        print()
    else:
        print(-1)

n=int(input())
l=[]
for i in range(n):
    x,y=map(int,input().split())
    l.append([x,y,i])
l = sorted(l , key=lambda e: e[1]-e[0])
# print(l)
solve(n, l)
 