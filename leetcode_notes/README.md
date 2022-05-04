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

## 2022-5-1

### 1305.两颗二叉搜索树的所有元素

学习到了STL中`merge()`函数和`inplace_merge()`函数的用法

```cpp
class Solution {
    vector<int> vec;
    void mid(TreeNode* root)
    {
        if (root == nullptr) return;
        mid(root->left);
        vec.push_back(root->val);
        mid(root->right);
    }
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        mid(root1);
        int n = vec.size();
        mid(root2);
        inplace_merge(vec.begin(), vec.begin() + n, vec.end());
        return vec;
    }
};
```

### 2256.最小平均差

前缀和+遍历模拟

```cpp
class Solution {
public:
    int minimumAverageDifference(vector<int>& nums) {
        int res = 0, mindis = INT_MAX;
        int n = nums.size();
        vector<long long> presum(n);
        presum[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            presum[i] = presum[i-1] + nums[i];
        }
        for (int i = 0; i < n; i++)
        {
            long long  a = presum[i] / (i + 1);
            long long b = i < n - 1 ? (presum.back() - presum[i]) / (n - i - 1) : 0;
            long long ab = abs(a - b);
            if (mindis > ab)
            {
                mindis = ab;
                res = i;
            }
        }
        return res;
    }
};
```

### 2257.统计网络图中没有被保卫的格子

基本思路是DFS，关键是处理好守卫和墙，以降低复杂度

```cpp
class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>> grid(m, vector<int>(n, 1));
        for (auto v : walls)
        {
            grid[v[0]][v[1]] = 0;
        }
        for (auto v : guards)
        {
            grid[v[0]][v[1]] = 0;
        }
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        
        for (auto v : guards)
        {
            int x = v[0], y = v[1];
            for (int i = 0; i < 4; i++)
            {
                int tx = x + dx[i], ty = y + dy[i];
                while (tx >= 0 && tx < m && 
                       ty >= 0 && ty < n && grid[tx][ty] != 0)
                {
                    grid[tx][ty] = -1;
                    tx += dx[i];
                    ty += dy[i];
                }
            }
        }
        int res = 0;
        for (auto v : grid)
        {
            for (int n : v)
                if (n == 1) res++;
        }
        return res;
    }
};
```

## 2022-5-2

### [牛客.分发糖果](https://ac.nowcoder.com/acm/problem/235159)

数学方法，列举几种情况进行判断

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int cnt;
        cin >> cnt;
        int num2 = 0, num3 = 0;
        for (int j = 0; j < cnt; j++)
        {
            int tmp;
            cin >> tmp;
            if (tmp == 2) num2++;
            else num3++;
        }
        int a = num3 % 3;
        int b = num2 % 3;
        if (a == 0)
        {
            if (b == 0) cout << "YES" << endl;
            else cout << "NO" <<  endl;
        }
        else if (a == 1)
        {
            if (num3 > 3 && num2 >= 3 && b == 0) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
        else
        {
            if (num2 >= 6 && b == 0) cout << "YES" <<  endl;
            else cout << "NO" << endl;
        }
    }
    return 0;
}
```

### [牛客.海滩网络](https://ac.nowcoder.com/acm/problem/236226)

最小生成树模板题，需要对可能的节点进行筛选优化

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
#define x first
#define y second
using ll = long long;
using P = pair<int, int>;

P a[N];
int p[N];
int n, m  = 0;

struct Edge{
    int a, b;
    ll w;
    bool operator < (const Edge & E) const
    {
        return w < E.w;
    }
} e[N * 25];

ll get_weight(int x1, int y1, int x2, int y2)
{
    ll dx = abs(x1 - x2), dy = abs(y1 - y2);
    return dx * dx + dy * dy;
}

int find(int x)
{
    if (p[x] == x) return p[x];
    return p[x] = find(p[x]);
}

void kruskal() 
{
    for (int i = 1; i <= n; i++) p[i] = i;
    sort(e + 1, e + 1 + m);
    ll ans = 0;
    for (int i = 1; i <= m; i++)
    {
        int x = find(e[i].a), y = find(e[i].b);
        if (x != y)
        {
            p[x] = y;
            ans += e[i].w;
        }
    }
    cout << ans <<  endl;
}
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= i + 20 && j <= n; j++)
        {
            e[++m] = {i, j, get_weight(a[i].x, a[i].y, a[j].x, a[j].y)};
        }
    }
    kruskal();
    return 0;
}

```

## 2022-5-3

### [937.重新排列日志文件](https://leetcode-cn.com/problems/reorder-data-in-log-files/)

自定义排序，没什么好说的，用到了`stable_sort()`函数，进行稳定排序，比较`sort()`是不稳定的

```cpp
class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        auto cmp = [](const string & a, const string & b){
            int pa = a.find(' '), pb = b.find(' ');
            if (isdigit(a[pa + 1])) return false;
            else if (isdigit(b[pb + 1])) return true;
            else
            {
                string loga = a.substr(pa + 1), logb = b.substr(pb + 1);
                if (loga == logb) return a.substr(0, pa) < b.substr(0, pb);
                else return loga < logb;
            }
        };
        stable_sort(logs.begin(), logs.end(), cmp);
        return logs;
    }
};
```

## 2022-5-4

### [1823.找出游戏的获胜者](https://leetcode-cn.com/problems/find-the-winner-of-the-circular-game/)

约瑟夫环模板题，之前做过还是不记得hhh，太草了
约瑟夫环的思路就是倒叙看待问题，先确定获胜者位置为0，然后倒着把每一步失败的人加进数组，同时再计算获胜者此时在数组中的位置，为什么用数组是为了**取模方面**，计算完后需要把数组下标转换为人的序号，迭代法更能体现这种思路

```cpp
// 递归
class Solution {
public:
    int findTheWinner(int n, int k) {
        if (n == 1) return 1;
        // 减1切换为数组下标进行求模运算，加1切换回人的编号
        return (findTheWinner(n - 1, k) + k - 1) % n + 1; 
    }
};
```

```cpp
// 迭代
class Solution {
public:
    int findTheWinner(int n, int k) {
        int p = 0;
        for (int i = 2; i <= n; i++)
            p = (p + k) % i;
        return p + 1;
    }
};
```

数组模拟做法

```cpp
class Solution {
public:
    int findTheWinner(int n, int k) {
        vector<int> lose(n, 0);
        int idx = 0, sz = n;
        while (n > 1)
        {
            for (int i = 0; i < k - 1; i++) // 移动k-1次
            {
                do idx++;
                while (lose[idx % sz]);
            }
            n--;
            lose[idx % sz] = 1;
            while (lose[idx % sz]) idx++;
        }
        return idx % sz + 1;
    }
};
```

队列模拟做法

```cpp
class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int> qu;
        for (int i = 1; i <= n; i++) {
            qu.emplace(i);
        }
        while (qu.size() > 1) {
            for (int i = 1; i < k; i++) {
                qu.emplace(qu.front());
                qu.pop();
            }
            qu.pop();
        }
        return qu.front();
    }
};
```

### [390.消除游戏](https://leetcode-cn.com/problems/elimination-game/)

运用约瑟夫环的思想，先固定最后剩下的数字的位置，然后找数学规律

数学规律的证明还是有点费劲的，[看这里](https://blog.csdn.net/afei__/article/details/83689502)

```cpp
class Solution {
public:
    int lastRemaining(int n) {
        // 这数据量，一看就不能暴力
        return n == 1 ? 1 : 2 * (n / 2 + 1 - lastRemaining(n / 2));
    }
};
```

也可以用等差数列的思路模拟，实质上也是先假设剩下的数字的位置，再倒推其原始位置

```cpp
class Solution {
public:
    int lastRemaining(int n) {
        int a1 = 1;
        int k = 0, cnt = n, step = 1;
        while (cnt > 1) {
            if (k % 2 == 0) { // 正向
                a1 = a1 + step;
            } else { // 反向
                a1 = (cnt % 2 == 0) ? a1 : a1 + step;
            }
            k++;
            cnt = cnt >> 1;
            step = step << 1;
        }
        return a1;
    }
};
```

