#include<bits/stdc++.h>
using namespace std;
const int MAXN = 7e5+5;
const int MAXM = 8e5+5;
const int MAXT = 4e5+5;

int lines, n;
map<string, int> pos;

int dis[MAXN];
bool vis[MAXN];

int dp[MAXN];
int point[MAXM];
int rear = 0;

int cnt = 1;
int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int weight[MAXN << 1];

struct Line {
    int u, d;
} nums[MAXT];

bool cmp(Line a, Line b) {
    return a.d < b.d;
}

struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> heap;

void addedge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dijkstra(int st) {
    for (int i = 1; i <= n + lines; i++) {
        dis[i] = INT_MAX;
        vis[i] = false;  // Initialize vis array
    }
    dis[st] = 0;
    heap.push({st, 0});
    while (!heap.empty()) {
        int u = heap.top().first;
        heap.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = weight[i];
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                heap.push({v, dis[v]});
            }
        }
    }
}

int main() {
    cin >> lines >> n;
    string name;
    for (int i = 1; i <= n; i++) {
        cin >> name;
        pos[name] = i;
    }
    for (int i = 1; i <= lines; i++) {
        int k;
        cin >> k;
        int u = n + i;
        for (int j = 1; j <= k; j++) {  // Changed i to j to avoid shadowing
            cin >> name;
            int v = pos[name];
            addedge(u, v, 1);
            addedge(v, u, 0);
        }
    }
    cin >> name;
    int st = pos[name];
    cin >> name;
    int en = pos[name];
    dijkstra(st);
    if (dis[en] == INT_MAX) {
        cout << -1 << endl;
        return 0;
    }
    cout<<dis[en]<<endl;
    for (int i = 1; i <= lines; i++) {
        nums[i].u = i + n;
        nums[i].d = dis[i + n];
    }
    sort(nums + 1, nums + lines + 1, cmp);
    for (int i = 1; i <= n; i++) {
        dp[i] = -1e9;
    }
    dp[st] = 0;
    for (int i = 1; i <= lines; i++) {
        int u = nums[i].u;
        if (dis[u] == INT_MAX) {
            break;
        }
        rear = 0;
        for (int j = head[u]; j; j = nxt[j]) {  
            int v = to[j];
            point[++rear] = v;
            // cout<<point[rear]<<' ';
        }
        // cout<<endl;
        int maxn = 0;
        //从前开始枚举
        for (int j = 1; j <= rear; j++) {
            int v = point[j];
            if (dis[v] == dis[u] + 1) {
                if (maxn != 0) {
                    dp[v] = max(dp[v], dp[point[maxn]] + j - maxn);
                }
            }
            else if (dis[v] == dis[u]) {
                if (maxn) {
                    if (dp[point[maxn]] - maxn < dp[point[j]] - j) maxn = j;
                } else {
                    maxn = j;
                }
            }
        }
        maxn = 0;
        //从后开始枚举
        for (int j = rear; j >= 1; j--) {
            int v = point[j];
            if (dis[v] == dis[u] + 1) {
                if (maxn != 0) {
                    dp[v] = max(dp[v], dp[point[maxn]] + maxn - j);
                }
            } else if (dis[v] == dis[u]) {
                if (maxn) {
                    if (dp[point[maxn]] + maxn < dp[point[j]] + j) maxn = j;
                } else {
                    maxn = j;
                }
            }
        }
    }
    cout << dp[en] << endl;  
    return 0;
}