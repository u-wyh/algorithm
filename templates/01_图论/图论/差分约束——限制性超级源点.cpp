// 倍杀测量者
// 如果 A的分数 >= B的分数 * k，k是正实数，就称 A k倍杀 B，或称 B被A k倍杀了
// 一场比赛中，一共有n个选手，有m1条誓言记录，有m2条选手得分记录，得分只可能是正实数
// 类型1的誓言 u v k : 选手u 没有k倍杀 选手v，那么选手u就穿女装
// 类型2的誓言 u v k : 选手u 被选手v k倍杀了，那么选手u就穿女装
// 选手的得分    u w : 选手u得了w分，如果某选手没有得分记录，按照尽量不穿女装的情况推测
// 你希望看到比赛后有人穿女装，但不想看到很多人穿女装，于是想制定正实数ans，效果如下
// 类型1的誓言，比例调整成(k-ans)，类型2的誓言，比例调整成(k+ans)，即提高了穿女装的条件
// 计算ans最大多少，依然有人穿女装，保留小数点后4位，如果不干预也没人穿女装，返回-1
// 1 <= n, m1, m2 <= 1000
// 1 <= k <= 10
// 1 <= w <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P4926
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//这道题将乘除关系通过log对数运算转换为加减运算
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1002;
const int MAXM = 3001;
const int MAXQ = 1000001;
const double INF = 1e10;
const double sml = 1e-6;

int n, m1, m2;

// 誓言记录(誓言类型, u, v, k)
int vow[MAXN][4];

// 得分记录(u, w)
int score[MAXN][2];

// 链式前向星需要
int head[MAXN];
int Next[MAXM];
int to[MAXM];
double weight[MAXM];
int cnt;

// spfa需要
double dis[MAXN];
int update[MAXN];
queue<int>q;
int h, t;
bool enter[MAXN];

//建立链式前向星
void addedge(int u, int v, double w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void build() {
    cnt = 1;
    fill(head, head+n + 2, 0);
    fill(enter,enter+ n + 2, false);
    fill(dis,dis+ n + 2, INF);
    fill(update,update+ n + 2, 0);
    while(!q.empty()){
        q.pop();
    }
}

bool spfa(int s) {
    dis[s] = 0;
    update[s]++;
    q.push(s) ;
    enter[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        enter[u] = false;
        for (int ei = head[u]; ei > 0; ei = Next[ei]) {
            int v = to[ei];
            double w = weight[ei];
            if (dis[u] + w < dis[v]) {
                //如果值变小了  那么就要改变
                dis[v] = dis[u] + w;
                if (!enter[v]) {
                    if (++update[v] > n+1) {
                        return true;
                    }
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}

// 是否有人穿女装
bool check(double limit) {
    build();
    // 0号点是连通超级源点，保证图的连通
    for (int i = 1; i <= n; i++) {
        //联通超级源点
        addedge(0, i, 0);
    }
    // 倍杀关系的建边
    for (int i = 1; i <= m1; i++) {
        if (vow[i][0] == 1) {
            addedge(vow[i][1], vow[i][2], -log(-limit + vow[i][3]));
        } else {
            // 因为类型2的誓言是<关系，所以减去最小精度后，就可以认为是<=关系
            addedge(vow[i][1], vow[i][2], log(limit + vow[i][3] - sml));
        }
    }
    // n+1号点是限制超级源点，保证确定得分的选手之间的关系
    // 本题测试数据有限，两个超级源点合并居然也能通过
    // 原理上两个超级源点一定要分开，课上进行了重点讲解
    for (int i = 1; i <= m2; i++) {
        //限制性超级源点
        addedge(n + 1, score[i][0], log(score[i][1]));
        addedge(score[i][0], n + 1, -log(score[i][1]));
    }
    return spfa(0);
}

double compute(){
    double l=0,r=INF,ans=-1;
    while(r-l>=sml){
        double mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+sml;
        }
        else{
            r=mid-sml;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m1>>m2;
    for(int i=1;i<=m1;i++){
        cin>>vow[i][0]>>vow[i][1]>>vow[i][2]>>vow[i][3];
    }
    for(int i=1;i<=m2;i++){
        cin>>score[i][0]>>score[i][1];
    }
    double ans=compute();
    if(ans==0){
        cout<<"-1"<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}