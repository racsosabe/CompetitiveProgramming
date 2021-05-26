l, r = [int(x) for x in input().split()]

b = 6
p = 2 ** b

pot = [1 << i for i in range(b)]

L = (r >> b) + 2
composite = [0 for i in range(L)]

i = 3
while i * i <= r:
    if (composite[i >> b] & pot[i % b]) == 0:
        for j in range(i * i, r + 1, i):
            composite[j >> b] |= pot[j % b]
    i += 2
ans = 0
if l <= 2 <= r: ans += 1
i = 5
while i <= r:
    if i >= l and (composite[i >> b] & pot[i % b]) == 0: ans += 1
    i += 4

print(ans)
