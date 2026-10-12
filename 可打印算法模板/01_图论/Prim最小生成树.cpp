// 用途：无向带权图最小生成树；输入 n m 和 m 条 u v w。
// 时间：O((n+m) log n)。
// 空间：O(n+m)。
// 注意：图不连通输出 orz；n<=5000，m<=2e5。
// 例题：https://www.luogu.com.cn/problem/P3366
// 题意：选若干边连通所有点，使总边权最小。
// 思路：从已有点集向外选最轻的跨集合边，直到纳入所有点。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5001;
const int MAXM = 400001;

int n, m;
int u, w;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

int heap[MAXN][2];
// where 记录点在堆中的位置，-1 未入堆，-2 已选入生成树。
int where[MAXN];
int heapSize;
int nodeCnt;

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool isEmpty() {
    return heapSize == 0;
}

void swap(int i, int j) {
    int a = heap[i][0];
    int b = heap[j][0];
    where[a] = j;
    where[b] = i;
    swap(heap[i],heap[j]);
}

void heapify(int i) {
    int l = i * 2 + 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1][1] < heap[l][1] ? l + 1 : l;
        best = heap[best][1] < heap[i][1] ? best : i;
        if (best == i) {
            break;
        }
        swap(best, i);
        i = best;
        l = i * 2 + 1;
    }
}

void pop() {
    u = heap[0][0];
    w = heap[0][1];
    swap(0, --heapSize);
    heapify(0);
    where[u] = -2;
    nodeCnt++;
}

void heapInsert(int i) {
    while (heap[i][1] < heap[(i - 1) / 2][1]) {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void addOrUpdateOrIgnore(int ei) {
    int v = to[ei];
    int w = weight[ei];
    if (where[v] == -1) {
        heap[heapSize][0] = v;
        heap[heapSize][1] = w;
        where[v] = heapSize++;
        heapInsert(where[v]);
    } else if (where[v] >= 0) {
        heap[where[v]][1] = min(heap[where[v]][1], w);
        heapInsert(where[v]);
    }
}

long long prim() {
    nodeCnt = 1;
    where[1] = -2;//将节点1直接视为已经弹出过了
    for (int ei = head[1]; ei > 0; ei = Next[ei]) {
        addOrUpdateOrIgnore(ei);
    }
    long long ans = 0;
    while (!isEmpty()) {
        pop();
        ans += w;
        for (int ei = head[u]; ei > 0; ei = Next[ei]) {
            addOrUpdateOrIgnore(ei);
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        where[i]=-1;
    }
    for (int i = 0, u, v, w; i < m; i++) {
        cin>>u>>v>>w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    long long ans = prim();
    if(nodeCnt == n)
        cout<< ans ;
    else
        cout<<"orz"<<endl;
    return 0;
}
