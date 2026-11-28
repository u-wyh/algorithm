// https://www.luogu.com.cn/problem/P3958
// 题意：T 组数据，奶酪高 h（下表面 z = 0，上表面 z = h），
// 内部有 n 个半径均为 r 的球形空洞，球心在 (x, y, z)。
// 相切或相交的空洞之间可互相通行
// 与下/上表面相切
// 或相交的空洞可与下/上表面通行
// （距离公式为三维欧氏距离
// sqrt((x1-x2)^2+(y1-y2)^2+(z1-z2)^2)）。
// 判断能否仅通过空洞从下表面到达上表面。
// 数据范围：1 <= T <= 20，1 <= n <= 10^3，
// 1 <= h, r <= 10^9，
// 坐标 x, y, z 的绝对值不超过 10^9。
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集
#include<bits/stdc++.h>
using namespace std;
//#define int long long

struct node{
    int x,y,z;
    long long low,high;
}nums[20005];
bool un[20005];
int cnt=1;//记录每次开始的编号

int fa[20005];

void build(int n){
    for(int i=cnt;i<=cnt+n-1;i++){
        fa[i]=i;
    }
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

bool check(int i,int j,int r){
    long long dis=pow(nums[i].x-nums[j].x,2)+pow(nums[i].y-nums[j].y,2)+pow(nums[i].z-nums[j].z,2);
    if(dis>4*r*r)
        return false;
    return true;
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        int n,h,r;
        cin>>n>>h>>r;
        build(n);
        for(int i=1;i<=n;i++){
            cin>>nums[cnt+i-1].x>>nums[cnt+i-1].y>>nums[cnt+i-1].z;
            nums[cnt+i-1].low=nums[cnt+i-1].z-r;
            nums[cnt+i-1].high=nums[cnt+i-1].z+r;
        }
        for(int i=2;i<=n;i++){
            for(int j=i-1;j<=n;j++){
                int a=find(cnt+i-1);
                int b=find(cnt+j-1);
                if(check(cnt+i-1,cnt+j-1,r)&&a!=b){
                    fa[b]=a;
                    nums[a].low=min(nums[a].low,nums[b].low);
                    nums[a].high=max(nums[a].high,nums[b].high);
                }
            }
        }
        int f=0;
        for(int i=1;i<=n;i++){
            if(fa[cnt+i-1]==cnt+i-1){
                if(nums[cnt+i-1].high>=h&&nums[cnt+i-1].low<=0){
                    cout<<"Yes\n";
                    f=1;
                    break;
                }
            }
        }
        if(f==0)
            cout<<"No\n";
        cnt=n+cnt-1;
    }
    return 0;
}
