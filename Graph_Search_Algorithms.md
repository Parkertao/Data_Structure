# 最短路径问题

> 以leetcode-743.网络延迟时间为例

## 多源最短路径算法

### Floyd算法

Floyd算法本质就是暴力搜索，时间复杂度$O(n^3)$，一般采用邻接矩阵存图，基本步骤：遍历中间节点、遍历源节点、遍历目标节点、松弛操作。

```c++
vector<vector<int>> graph(n + 1, vector<int>(n + 1, inf));
// 初始化邻接矩阵
for (int i = 1; i <= n; i++)
{
    graph[i][i] = 0;
}
// 存图
for (auto v : times)
{
	graph[v[0]][v[1]] = v[2];
}

void Floyd(int n) //n为节点个数
{
    for (int k = 1; k <= n; k++) //遍历中间节点
    {
        for (int i = 1; i <= n; i++) //遍历源节点
        {
            for (int j = 1; j <= n; j++) //遍历目标节点
            {
                graph[i][j] = std::min(graph[i][j], graph[i][k][graph[k][j]]); //松弛操作
            }
        }
    }
}
```



## 单源最短路劲算法

### Dijkstra算法

迪杰斯特拉算法基于贪心思想，针对边**没有负权值的图**。

1. 初始化距离列表：起点到起点的距离为0，其余节点为inf
2. 初始化访问列表，所有节点均为**未访问状态**
3. 开始迭代n次（节点数），每次迭代先在距离列表中找到与源节点最小距离的点
4. 用该点去更新所有点到源点的距离

> 朴素Dijkstra算法，时间复杂度为$O(n^2)$。

```c++
const int inf = 100000;
vector<vector<int>> graph(n + 1, vector<int>(n + 1, inf));
// 初始化邻接矩阵
for (int i = 1; i <= n; i++)
{
	graph[i][i] = 0;
}
// 存图
for (auto v : times)
{
	graph[v[0]][v[1]] = v[2];
}
// 初始化距离列表
vector<int> dist(n + 1, inf);
// 初始化访问列表
vector<int> vis(n + 1, 0);
dist[k] = 0;
// vis[k] = 1; 不可以先标记源节点
for (int p = 1; p <= n; p++)
{
	// 每次迭代找到-最短距离最小-且-没有被访问过-的点
	int t = -1;
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i] && (t == -1 || dist[i] < dist[t])) t = i;
	}
	vis[t] = 1;
	// 用点t的-最小最短距离-更新其他点
    // 实际上就是更新与t相接的节点
	for (int i = 1; i <= n; i++)
	{
        // 松弛操作
		dist[i] = min(dist[i], dist[t] + graph[t][i]);
	}
}
```

> 使用堆优化Dijkstra算法，时间复杂度$O(m\log(n)+n)$

```c++
const int inf = 100000;
// 邻接表
vector<unordered_map<int, int>> graph;
graph.resize(n + 1);
// 存图
for (auto v : times)
{
    graph[v[0]][v[1]] = v[2];
}
// 初始化距离列表
vector<int> dist(n + 1, inf);
dist[k] = 0;
vector<int> vis(n + 1, 0);
// 距离和目标节点
using P = pair<int,int>;
priority_queue<P, vector<P>, greater<P>> pq;
pq.emplace(0, k);

while (!pq.empty())
{
    // 直接取出与源节点最短距离的节点
	P tmp = pq.top();
	pq.pop();
    // 已更新过的节点跳过
	if (vis[tmp.second]) continue;
    vis[tmp.second] = 1;
    
    // 遍历与当前节点相连的节点
    for (auto& e : graph[tmp.second])
    {
        // 松弛操作
        if (dist[e.first] > e.second + tmp.first)
        {
            dist[e.first] = e.second + tmp.first;
            pq.emplace(e.second + tmp.first, e.first);
        }
    }
}
```

### Bellman-Ford算法

Bellman-Ford算法可以对负权图求最短路，**时间复杂度为$O(nm)$**。

Bellman-Ford算法需要一个一维数组dist来储存每个点到源节点的距离，第一次遍历，可以求得源节点一步可达节点的dist距离，第二次遍历，可以求得源节点两步可达节点的dist距离，以此类推。

```c++
const int inf = 100000;
// 邻接表
vector<unordered_map<int, int>> graph;
graph.resize(n + 1);
// 存图
for (auto v : times)
{
    graph[v[0]][v[1]] = v[2];
}
// 初始化距离列表
vector<int> dist(n + 1, inf);
dist[k] = 0;
// 迭代n-1次
for (int i = 1; i < n; i++)
{
    // 遍历每一条边，执行松弛操作
    for (int j = 1; j <= n; j++) // 各一个节点
    {
        for (auto e : graph[j]) // 每一个节点相连的边
        {
            dist[e.first] = std::min(dist[e.first], dist[j] + e.second);
        }
    }
}
```

### SPFA算法

SPFA算法是对Bellman-Ford算法的优化，Bellman-Ford算法每次遍历只能更新上一次被更新过的节点所直接相连的节点，其余的节点则可以不用重复去更新。SPFA算法采用队列来对此进行优化，**只让当前节点相连的节点入队，如果一个节点已经在队列里，就不重复入队，如果一条边未被更新，那么它的终点不入队**。

SPFA算法**时间复杂度为$O(mn)$**

```c++
const int inf = 100000;
// 邻接表
vector<unordered_map<int, int>> graph;
graph.resize(n + 1);
// 存图
for (auto v : times)
{
    graph[v[0]][v[1]] = v[2];
}
// 初始化距离列表
vector<int> dist(n + 1, inf);
dist[k] = 0;
// 初始化队列
queue<int> q;
q.push(k);
// 初始化队列记录表
vector<int> inqueue(n + 1, 0);
inqueue[k] = 1;

while (!q.empty())
{
    int tmp = q.front();
    q.pop();
    inqueue[tmp] = 0;
    // 遍历当前节点相连的边
    for (auto& e : graph[tmp])
    {
        // 松弛操作
        if (dist[e.first] > dist[tmp] + e.second)
        {
            dist[e.first] = dist[tmp] + e.second;
            // 如果节点不在队列中，则入队
            if (!inqueue[e.first])
            {
                q.push(e.first);
                inqueue[e.first] = 1;
            }
        }
    }
}
```

