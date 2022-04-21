## 2022-4-20

### 200.岛屿数量

```c++
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == '1')
                {
                    res++;
                    dfs(grid, i, j);
                }
            }
        }
        return res;
    }
private:
    void dfs(vector<vector<char>>& grid, int i, int j)
    {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == '0') return;
        grid[i][j]='0';//把岛给淹了，真是妙，一直没想到这一步，搞死人
        dfs(grid, i+1, j);
        dfs(grid, i-1, j);
        dfs(grid, i, j+1);
        dfs(grid, i, j-1);
    }
};
```

图搜索的几个关键点：**建图，dfs、bfs等算法模板，标记访问**

### 547.省份数量

同上一题，都是搜索，并且做好标记，因为是相当于找连通分量，所以一般都是用DFS。

```c++
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        vector<int> path(isConnected.size(), 0);
        int res = 0;
        for (int i = 0; i < isConnected.size(); i++)
        {
            if (!path[i])
            {
                res++;
                dfs(isConnected, i, path);
            }
        }
        return res;
    }
private:
    void dfs(vector<vector<int>>& isConnected, int s, vector<int>& path)
    {
        path[s] = 1;
        for(int i = 0; i < isConnected.size(); i++)
        {
            if(isConnected[s][i]&& !path[i])
                dfs(isConnected, i, path);
        }
    }
};
```

### 1319.连通网络的操作次数

一开始的思路是通过dfs搜索有多少个连通分量，以及多少个多余的线缆，然后通过多余线缆数和连通分量数比较来判断是否能全部连接起来。但是dfs搜索来判断多余线缆数很困难。

看了题解才知道**根本不需要知道多余线缆，只需要总线缆数大于等于节点数减一即可**，证明也很简单，甚至说不用证明，一个图里如果用两个独立的连通分量，那么边数必然小于n-1，只要边数大于等于n-1，那么就可以通过断开重连使两个分量连通。

这样思路就变得十分简单，就是模板题了。

```c++
// 搜索找到有多少个网络，有多少多余的线缆
// 线缆数大于网络数减一，就可以实现全连通，否则不能
// 
// 思路错误的点：找到多少多余线缆比较困难，判断是否能全部连通，是通
// 过总线缆数和总节点数-1比较得到，这样就无需在搜索时关注多余线缆数

class Solution {
    void dfs(int v, vector<int>& vis, vector<vector<int>>& edge)
    {
        vis[v] = 1;
        for (auto e : edge[v])
        {
            if (!vis[e]) dfs(e, vis, edge);
        }
    }
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1) return -1;
        int nets = 0;
        vector<int> vis(n, 0);
        vector<vector<int>> edge(n);
        // 建图，邻接表
        for (auto v : connections)
        {
            edge[v[0]].push_back(v[1]);
            edge[v[1]].push_back(v[0]);
        }

        for (int i = 0; i < n; i++)
        {
            if (!vis[i])
            {
                dfs(i, vis, edge);
                nets++;
            }
        }
        return nets - 1;
    }
};
```

并查集解法

```c++
// 并查集模板
class UnionFind {
public:
    vector<int> parent;
    vector<int> size;
    int n;
    // 当前连通分量数目
    int setCount;
    
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0); // 自增填充函数
    }
    
    int findset(int x) {
        return parent[x] == x ? x : parent[x] = findset(parent[x]);
    }
    
    bool unite(int x, int y) {
        x = findset(x);
        y = findset(y);
        if (x == y) {
            return false;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }
    
    bool connected(int x, int y) {
        x = findset(x);
        y = findset(y);
        return x == y;
    }
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1) {
            return -1;
        }

        UnionFind uf(n);
        for (const auto& conn: connections) {
            uf.unite(conn[0], conn[1]);
        }

        return uf.setCount - 1;
    }
};
```

## 2022-4-21

### 1162.地图分析

标准的BFS搜索题，跟前两天做的542.01矩阵题异曲同工，摘抄一下当时的笔记

>多源bfs，所谓多源，就是多个起点，在图的应用bfs，实际上就是多源，但是一般第一步并不是，因为第一步通常是从一个源起点开始遍历的，所以之前对所谓的多源BFS总是没什么理解，但是到了第二步就是很明显的多源了，因为第一步把跟起点联通的节点全都加入队列了。
>
>那么这一题，其实就是一个从第二步开始BFS的过程的一个具象，虽然是问一个1节点到一个0节点的最短距离，实际上可以反向考虑，即0节点到离他最近的1节点的距离，这样就可以把问题转变为典型的BFS，即以过个0节点为源，出发搜索1节点，并且由于是BFS可以保证搜索到的1节点是距离最近的。

```c++
// 标准BFS
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        using P = pair<int, int>;
        int n = grid.size();
        queue<P> q;
        vector<vector<int>> dis(grid);
        // 把所有陆地加进队列，作为源节点
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j])
                {
                    dis[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        // 判断是否都是海洋或者陆地
        if (q.size() == n * n || q.empty()) return -1;
        int res = 0;
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        while (!q.empty())
        {
            int sz = q.size();
            for (int i = 0; i < sz; i++)
            {
                int x = q.front().first, y = q.front().second;
                q.pop();
                for (int i = 0; i < 4; i++)
                {
                    int tx = x + dx[i], ty = y + dy[i];
                    if (tx >= 0 && tx < n && ty >= 0 && ty < n && !grid[tx][ty])
                    {
                        grid[tx][ty] = 1;
                        q.push({tx, ty});
                        // 记录从源出发的距离
                        dis[tx][ty] = dis[x][y] + 1;
                        // 记录最远距离
                        res = max(res, dis[tx][ty]);
                    }
                }
            }
        }
        return res;
    }
};
```

### 1926.迷宫中离入口最近的出口

也是基础的BFS找最短路径，grid地图用BFS真就足够了，到graph上再用dijkstra之类的高级一点的算法。

```c++
// BFS
class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size(), n = maze[0].size();
        using P = pair<int, int>;
        queue<P> q;
        q.push({entrance[0], entrance[1]});
        maze[entrance[0]][entrance[1]] = '+';
        int res = 0;
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        while (!q.empty())
        {
            int sz = q.size();
            for (int i = 0; i < sz; i++)
            {
                int x = q.front().first, y = q.front().second;
                q.pop();
                if ((x != entrance[0] || y != entrance[1]) && (x == 0 || x == m - 1 || y == 0 || y == n - 1)) return res;
                for (int k = 0; k < 4; k++)
                {
                    int tx = x + dx[k], ty = y + dy[k];
                    if (tx >= 0 && tx < m && ty >= 0 && ty < n && maze[tx][ty] == '.')
                    {
                        maze[tx][ty] = '+';
                        q.push({tx, ty});
                    }
                }
            }
            res++;
        }
        return -1;
    }
};
```

