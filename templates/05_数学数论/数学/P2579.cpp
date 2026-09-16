//P2579
//这道题目如果理解了  那么可以说算是掌握了矩阵乘法的原理
//2 3 4 是间隔时间 他们的最小公约数是12  也就是相当于12个为一次循环
//那么我们直接建立12个矩阵  表示在时刻为i的时候那些边可以走
//首先将12个图中的所有本来就可以走的边设置为1
//然后根据时间判断那些边是不能走的
//将单位矩阵和这12个矩阵相乘  计算他的t/12次方
//然后将剩余的部分走完即可
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e4;

int n,m;
int st,en,t;
int fish;
int to[4];
struct mat{
    vector<vector<int>>f;
    mat(int n,int m): f(n,vector<int>(m,0)){}
};

mat operator*(mat a,mat b){
    int n=a.f.size();
    int m=b.f[0].size();
    int k=a.f[0].size();
    mat ans(n,m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int p=0;p<k;p++){
                ans.f[i][j]+=a.f[i][p]*b.f[p][j];
                ans.f[i][j]%=MOD;
            }
        }
    }
    return ans;
}

mat power(mat a,int p){
    int n=a.f.size();
    mat base(n,n);
    for(int i=0;i<n;i++){
        base.f[i][i]=1;
    }
    while(p){
        if(p&1){
            base=base*a;
        }
        p>>=1;
        a=a*a;
    }
    return base;
}

int main()
{
    cin>>n>>m>>st>>en>>t;
    vector<mat> g(13, mat(n,n));
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        for (int j = 1; j <= 12; j++) {
            g[j].f[x][y] = g[j].f[y][x] = 1;
        }
    }
    cin>>fish;
    while(fish--){
        int num;
        cin>>num;
        for(int i=0;i<num;i++){
            cin>>to[i];
        }
        for(int i=0;i<n;i++){
            for(int j=1;j<=12;j++){
                g[j].f[i][to[j%num]]=0;
            }
        }
    }
    mat base(n,n);
    for(int i=0;i<n;i++){
        base.f[i][i]=1;
    }
    for(int i=1;i<=12;i++){
        base=base*g[i];
    }
    mat ans=power(base,t/12);
    for(int i=1;i<=t%12;i++){
        ans=ans*g[i];
    }
    cout<<ans.f[st][en];
    return 0;
}
