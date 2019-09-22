MAX_value = float('inf') 
def dijkstra(graph,src):
  if graph ==None:
    return None
  # 定点集合
  nodes = [i for i in range(len(graph))] # 获取顶点列表，用邻接矩阵存储图
  # 顶点是否被访问
  visited = []
  visited.append(src)
  # 初始化dis
  dis = {src:0}# 源点到自身的距离为0
  for i in nodes:
    dis[i] = graph[src][i]
  path={src:{src:[]}} # 记录源节点到每个节点的路径
  k=pre=src
  while nodes:
    temp_k = k
    mid_distance=float('inf') # 设置中间距离无穷大
    for v in visited:
      for d in nodes:
        if graph[src][v] != float('inf') and graph[v][d] != float('inf'):# 有边
          new_distance = graph[src][v]+graph[v][d]
          if new_distance <= mid_distance:
            mid_distance=new_distance
            graph[src][d]=new_distance # 进行距离更新
            k=d
            pre=v
    if k!=src and temp_k==k:
      break
    dis[k]=mid_distance # 最短路径
    path[src][k]=[i for i in path[src][pre]]
    path[src][k].append(k)

    visited.append(k)
    nodes.remove(k) 
  return dis,path


n = int(input())
graph = [[MAX_value]*n for i in range(n)]
for i in range(n):
    graph[i][i] = 0
dgs = [0] * n
for i in range(n-1):
    x, y, l = map(int, input().split())
    graph[x-1][y-1] = l
    graph[y-1][x-1] = l
    dgs[x-1] += 1
    dgs[y-1] += 1
leaves = []
for i in range(n):
    if dgs[i] == 1:
        leaves.append(i)

min_dis = MAX_value
for i in range(len(leaves)):
    dist, _ = dijkstra(graph, leaves[i]) 
    for j in range(i+1, len(leaves)):
        min_dis = min(min_dis, dist[leaves[j]])
print(min_dis)

