"""
'X' 不能走
'.'能走两次

'#'能走一次
问是否能走到终点而且恰好让终点变成'X'

2
4 6
X...XX
...XX.
.X..X.
......
1 6
2 2
9 47
....X.X.X.X...X..X.....X..X..X..X....X.X...X..X
XX..X...X.........X...X...X..X.XX......X...X...
..XX...X.......X.....X.....X.XX..X.....X..XX...
.X...XX....X...X.......X.X...X......X.X.X......
X......X..X.XXX....X...X.X.XX..X.......X....X.X
....XX.X...X.XXX.X..XX.XXX...XXX..XX.X.X.XX..XX
.........X...X.XXXX...XX.XX....XX..X...X....X..
.............X....XXXX....X.X...XX.XX.X.X..X...
.X......X.....X......X......X.X.X..X.......XXX.
2 34
7 30

"""

def solver(board, start, end):
    
    sx, sy = start
    ex, ey = end
    n = len(board)
    m = len(board[0]) 
    def inbound(x, y):
        if x >= n or x < 0 or y >= m or y < 0:
            return False
        return True

    if board[ex][ey] == 'X':
        return False
    if board[ex][ey] == '.':
        count = 0
        if (not inbound(ex + 1, ey)) or board[ex+1][ey] == 'X':
            count += 1
        if (not inbound(ex-1, ey)) or board[ex-1][ey] == 'X':
            count += 1
        if (not inbound(ex, ey+1)) or board[ex][ey+1] == 'X':
            count += 1
        if (not inbound(ex, ey-1)) or board[ex][ey-1] == 'X':
            count += 1
        
        if count >= 3:
            return False
            
    def dfs(sx, sy):
        if sx >= n or sx < 0 or sy >= m or sy < 0:
            return False
        if (board[sx][sy] == 'X'):
            return False
        else:
            org = board[sx][sy] 
            if org == '#' and sx == ex and sy == ey:
                return True
            if org == '.' and sx == ex and sy == ey:
                cc = 0
                if (not inbound(ex + 1, ey)) or board[ex+1][ey] == 'X':
                    cc += 1
                if (not inbound(ex-1, ey)) or board[ex-1][ey] == 'X':
                    cc += 1
                if (not inbound(ex, ey+1)) or board[ex][ey+1] == 'X':
                    cc += 1
                if (not inbound(ex, ey-1)) or board[ex][ey-1] == 'X':
                    cc += 1 
                if cc >= 3:
                    return False

            board[sx][sy] = '#' if org == '.' else 'X'
            dx = 1 if ex > sx else -1
            dy = 1 if ey > sy else -1
            if dfs(sx+dx, sy):
                return True
            elif dfs(sx, sy + dy):
                return True
            elif dfs(sx-dx, sy):
                return True
            elif dfs(sx, sy-dy):
                return True 
            board[sx][sy] = org
            return False
    dx = 1 if ex > sx else -1
    dy = 1 if ey > sy else -1    
    return dfs(sx+dx, sy) or dfs(sx, sy+dy) or dfs(sx-dx, sy) or dfs(sx, sy - dy)

T = int(input())
for _ in range(T):
    n, m = list(map(int, input().split()))
    board = []
    for _ in range(n):
        board.append(list(input()))  
    sx, sy = list(map(int, input().split()))
    ex, ey = list(map(int, input().split()))

    if solver(board, (sx-1, sy-1), (ex-1, ey-1)):
        print('YES')
    else:
        print('NO')



