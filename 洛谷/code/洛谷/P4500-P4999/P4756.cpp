// https://www.luogu.com.cn/problem/P4756
// 输入：第一行两个整数 N, M，分别表示数组长度和询问次数。
// 输入：第二行 N 个整数，表示初始数组 a。
// 输入：接下来 M 行，每行一个整数 x_i。
// 题意：定义 f(i,j) = |sum_{p=i}^j a_p|，
// 数组的美丽度定义为 max_{1<=i<=j<=N} f(i,j)。
// 题意：设上一次询问的答案为 pre（第一次询问前 pre = 0）。
// 题意：第 i 次询问时，
// 在初始数组基础上给
// 每个元素加上 ((x_i + pre) % (4N + 1) - 2N)，
// 然后求当前数组的美丽度。
// 题意：算法必须在线回答。
// 输出：输出 M 行，第 i 行一个整数表示第 i 次询问的美丽度。
// 数据范围：1 <= N, M <= 2 * 10^5
// 数据范围：|a_i| <= 2 * 10^5
// 数据范围：0 <= x_i <= 8 * 10^5
// 算法标签：凸包、二分查找、前缀和
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m;

struct Point{
    int x,y;
};
Point p[MAXN];

Point up[MAXN];
Point dn[MAXN];
int cntup;
int cntdn;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

void Andrew(){
    for(int i=0;i<=n;i++){
        while(cntup>=2 && cross(up[cntup]-up[cntup-1],p[i]-up[cntup])>=0){
            cntup--;
        }
        up[++cntup]=p[i];

        while(cntdn>=2 && cross(dn[cntdn]-dn[cntdn-1],p[i]-dn[cntdn])<=0){
            cntdn--;
        }
        dn[++cntdn]=p[i];
    }
}

int calc(Point p,int x){
    return p.x*x+p.y;
}

int querymax(int x){
    int l=1,r=cntup;
    while(l<r){
        int mid=(l+r)>>1;
        if(calc(up[mid],x)<=calc(up[mid+1],x)){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    return calc(up[l],x);
}

int querymin(int x){
    int l=1,r=cntdn;
    while(l<r){
        int mid=(l+r)>>1;
        if(calc(dn[mid],x)>calc(dn[mid+1],x)){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    return calc(dn[l],x);
}

signed main()
{
    cin>>n>>m;

    p[0]={0,0};
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        p[i]={i,a+p[i-1].y};
    }

    Andrew();

    int pre=0;
    while(m--){
        int x;
        cin>>x;
        x=(x+pre)%(4*n+1)-2*n;
        pre=querymax(x)-querymin(x);
        cout<<pre<<endl;
    }
    return 0;
}
