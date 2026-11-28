// https://www.luogu.com.cn/problem/P3631
// 题意：输入表格行数 n、列数 m、已染色格数 k，
// 以及 k 个已染红（c_i=1）
// 或蓝（c_i=0）的方格坐标 (x_i, y_i)。
// 给剩余所有方格染成红或蓝色，
// 要求表格中每个 2*2 子正方形都恰好包含奇数个（1 个或 3 个）红色方格。
// 输出合法染色方案数对 10^9 取模的结果。
// 数据范围：2 <= n, m <= 10^5，0 <= k <= 10^5，
// 1 <= x_i <= n，1 <= y_i <= m，c_i in {0
// 1}。
// 难度评分：2300（洛谷分级换算）
// 算法标签：扩展域并查集、快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9;
const int MAXN = 1e5+5;

int n,m,k;
int fa[MAXN<<2];

int x[MAXN];
int y[MAXN];
int v[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline int id(int x,int y){
    return x*y+((y>1)?(n-1):0);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(fx>fy){
            swap(fx,fy);
        }
        fa[fy]=fx;
    }
}

signed main()
{
    n=read(),m=read(),k=read();
    bool has11=false;
    int a11=0;
    for(int i=1;i<=k;i++){
        x[i]=read(),y[i]=read(),v[i]=read();
        if(x[i]==1&&y[i]==1){
            has11=true;
            a11=v[i];
        }
    }
    int ans=0;
    int delta=n+m-1;


    for(int a=0;a<=1;a++){
        if(has11&&a!=a11){
            continue;
        }

        bool flag=false;
        for(int i=1;i<=2*(n+m-1);i++){
            fa[i]=i;
        }
        for(int i=1;i<=k;i++){
            if(x[i]==1&&y[i]==1){
                continue;
            }

            int op;
            if(x[i]%2||y[i]%2){
                op=0;
            }
            else{
                op=1;
            }

            if(x[i]==1||y[i]==1){
                int d=id(x[i],y[i]);
                if(v[i]==1){
                    un(1,d);
                    un(1+delta,d+delta);
                }
                else{
                    un(d,1+delta);
                    un(d+delta,1);
                }
            }
            else{
                op^=a;
                op^=v[i];
                if(op==1){
                    un(id(x[i],1)+delta,id(1,y[i]));
                    un(id(x[i],1),id(1,y[i])+delta);
                }
                else{
                    un(id(x[i],1),id(1,y[i]));
                    un(id(x[i],1)+delta,id(1,y[i])+delta);
                }
            }
        }
        if(flag){
            break;
        }

        for(int i=1;i<delta;i++){
            if(find(i)==find(i+delta)){
                flag=true;
                break;
            }
        }
        if(flag){
            break;
        }
        int kind=0;
        for(int i=1;i<=2*(n+m-1);i++){
            if(i==find(i)){
                kind++;
            }
        }
        kind=(kind-2)/2;
        ans=(ans+power(2,kind))%MOD;
    }
    cout<<ans<<endl;
    return 0;
}