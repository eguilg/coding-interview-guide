from functools import lru_cache
N, M, D = list(map(int, input().split()))
sp_nodes = list(map(int, input().split()))
fathers = list(map(int, input().split()))

tree = {}
for idx, f in enumerate(fathers):
    if f in tree:
        tree[f].append(idx+2)
    else:
        tree[f] = [idx+2]
 
@lru_cache(10000)
def bfs(node, d):
    ans = set([node])
    if d == 0:
        return ans
    if node in tree.keys():
        for n in tree[node]:
            if n not in ans:
                ans.update(bfs(n, d-1))
    if node-2 < len(fathers) and node-2 >= 0:
        if fathers[node-2] not in ans:
            ans.update(bfs(fathers[node-2], d-1)) 
    return ans

ret = None
for n in sp_nodes: 
    if ret == None:
        ret = bfs(n, D) 
    else:
        ret.intersection_update(bfs(n, D))
        
if ret == None:
    print(0)
else:
    print(len(ret))
