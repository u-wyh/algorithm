// https://www.luogu.com.cn/problem/P1715
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 305;

int n;
struct Point{
    int x,y;
};
Point p[MAXN];

bitset<MAXN>lft[MAXN][MAXN];
bitset<MAXN>pre[MAXN];
int ord[MAXN];
int ans[MAXN];
int now;

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

bool cmp1(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

bool cmp(int a,int b){
    int cr=cross(p[a]-p[now],p[b]-p[now]);
    return cr>0;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    sort(p+1,p+n+1,cmp1);
    for(int a=1;a<=n;a++){
        for(int b=1;b<=n;b++){
            if(a!=b){
                for(int c=1;c<=n;c++){
                    if(a==c || b==c){
                        continue;
                    }
                    if(cross(p[b]-p[a],p[c]-p[a])>0){
                        lft[a][b].set(c);
                    }
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        int m=0;
        for(int j=i+1;j<=n;j++){
            ord[++m]=j;
        }
        now=i;
        sort(ord+1,ord+m+1,cmp);
        pre[0].reset();
        for(int t=1;t<=m;t++){
            pre[t]=pre[t-1];
            pre[t].set(ord[t]);
        }
        for(int a=1;a<=m;a++){
            int pa=ord[a];
            for(int b=a+1;b<=m;b++){
                int pb=ord[b];
                bitset<MAXN>innode=pre[b-1]^pre[a];
                int cnt=(lft[pa][pb]&innode).count();
                ans[cnt]++;
            }
        }
    }
    for(int v=0;v<=n-3;v++){
        cout<<ans[v]<<endl;
    }
    return 0;
}