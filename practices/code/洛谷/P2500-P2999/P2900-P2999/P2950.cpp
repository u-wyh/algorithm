// https://www.luogu.com.cn/problem/P2950
// 题意：输入直线数量 N 和圆形绣花箍半径 d（圆心在原点 (0,0)），
// 以及 N 条互不重合直线的整数方程系数 a, b
// c（ax + by + c = 0）。
// 每条直线截取圆内的弦（部分直线可能不穿过圆内部），
// 且圆周上没有两条线共享同一端点。
// 统计在距离原点不超过 d
// 的布料范围内相交的线段对数量
// （若 k 条线交于同一点，算作 C(k, 2) 对相交）。
// 输出一行一个整数，表示相交的线段对数量。
// 数据范围：对于 100% 的数据，2 <= N <= 5*10^4，
// 1 <= d <= 5*10^4，
// -10^6 <= a, b, c <= 10^6。
// 难度评分：2000（洛谷分级换算）
// 算法标签：计算几何、扫描线、树状数组
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define N 100010
int n,num,c[N],vis[N];
long long ans,d;
const double eps=1e-9;
struct node{
    double ct;
    int id;
}p[N];
bool cmp(node x,node y){
    return x.ct-y.ct>eps;
}
int lowbit(int x){return x&(-x);}
void update(int p,int x){
    while(p<=2*n){
        c[p]+=x;
        p+=lowbit(p);
    }
}
long long query(int p){
    long long sum=0;
    while(p){
        sum+=c[p];
        p-=lowbit(p);
    }
    return sum;
}
int main(){
    //freopen("Cola.txt","r",stdin);
    scanf("%d%lld",&n,&d);
    long long a,b,c;
    for(int i=1;i<=n;i++){
        scanf("%lld%lld%lld",&a,&b,&c);
        //cin>>a>>b>>c;
        if(c*c<d*d*(a*a+b*b)){
            double tmp=a*a+b*b,tmp2=sqrt(d*d*tmp-c*c);
            double x1=(a*c+b*tmp2)/tmp;
            double x2=(a*c-b*tmp2)/tmp;
            double y1=(b*c-a*tmp2)/tmp;
            double y2=(b*c+a*tmp2)/tmp;
            p[++num].ct=atan2(y1,x1);p[num].id=i;
            p[++num].ct=atan2(y2,x2);p[num].id=i;
        }
    }
    sort(p+1,p+1+num,cmp);
    for(int i=1;i<=num;i++){
        if(vis[p[i].id]){
            ans+=query(i)-query(vis[p[i].id]);
            update(vis[p[i].id],-1);
        }
        else {
            vis[p[i].id]=i;
            update(i,1);
        }
    }
    printf("%lld",ans);
    return 0;
}