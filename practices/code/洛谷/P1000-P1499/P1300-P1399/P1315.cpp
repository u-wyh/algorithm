// https://www.luogu.com.cn/problem/P1315
// 题意：公交车 t=0 从 1 号点出发依次开往 2..n 号点，
// 相邻两站行驶耗时 D_i 分钟。
// 题意：有 m 名乘客
// （T_i 到达 A_i，需乘到 B_i 且 A_i < B_i），
// 每站须等所有该站出发乘客到齐才发车。
// 题意：有 k 个加速器可使任意 D_i 减
// 1（可重复用但须保持 D_i >= 0），求所有乘客总旅行时间最小值。
// 输入：第 1 行 n, m, k；第 2 行 n-1 个数 D_i；
// 后 m 行每行输入 T_i, A_i, B_i。
// 输出：输出一个整数表示最小总旅行时间。
// 数据范围：1 <= n <= 10^3，1 <= m <= 10^4，
// 0 <= k <= 10^5。
// 数据范围：0 <= D_i <= 100，0 <= T_i <= 10^5。
// 难度评分：1600（洛谷分级换算）
// 算法标签：贪心、排序、模拟
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 1e4+5;

int n,m,k;
int d[MAXN];
struct node{
    int t,st,en;
}nums[MAXM];
struct COUNT{
    int cnt,sub;
}arr[MAXN];
int tim[MAXN];
int beg[MAXN];
int ove[MAXN];

bool cmp(COUNT a,COUNT b){
    return a.cnt>b.cnt;
}

int main()
{
    cin>>n>>m>>k;
    for(int i=2;i<=n;i++){
        cin>>d[i];
        arr[i].sub=i;
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].t>>nums[i].st>>nums[i].en;
        tim[nums[i].st]=max(tim[nums[i].st],nums[i].t);
        arr[nums[i].en].cnt++;
    }
    sort(arr+1,arr+n+1,cmp);
    for(int i=1;i<=n;i++){
        if(k<=0||arr[i].sub==1){
            break;
        }
        if(k>=d[arr[i].sub]){
            k-=d[arr[i].sub];
            d[arr[i].sub]=0;
        }
        else{
            d[arr[i].sub]-=k;
            k=0;
        }
    }
    beg[1]=ove[1]=tim[1];
    for(int i=2;i<=n;i++){
        ove[i]=beg[i-1]+d[i];
        beg[i]=max(tim[i],ove[i]);
    }
    long long ans=0;
    for(int i=1;i<=m;i++){
        ans+=ove[nums[i].en]-nums[i].t;
    }
    cout<<ans<<endl;
    return 0;
}