// https://www.luogu.com.cn/problem/P12736
// 题意：给定若干区间相等约束，求长度为 n 的序列最多可用多少种不同颜色。
// 输入：首行 n, m，后 m 行每行三个整数 a_i, b_i, l_i。
// 规则：要求区间 [a_i, a_i+l_i-1] 与 [b_i, b_i+l_i-1] 对应位置同色。
// 输出：输出一个正整数，表示序列最多可包含的不同颜色种数。
// 数据范围：2 <= n <= 5*10^5，1 <= m <= 5*10^5。
// 数据范围：1 <= a_i, b_i <= n-l_i+1，a_i != b_i，l_i >= 1。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXH = 22;

int n,m;
int fa[MAXN][MAXH];
int one[MAXN];

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

int find(int i,int j){
    return fa[i][j]==i?i:fa[i][j]=find(fa[i][j],j);
}

void un(int x,int y,int k){
    int fx=find(x,k);
    int fy=find(y,k);
    if(fx!=fy){
        fa[fx][k]=fy;
    }
}

int main()
{
    n=read(),m=read();

    one[0]=-1;
    for(int i=1;i<=n;i++){
        one[i]=one[i>>1]+1;
    }

    for(int i=1;i<=n;i++){
        for(int j=0;j<=one[n];j++){
            fa[i][j]=i;
        }
    }

    for(int i=1;i<=m;i++){
        int l1=read();
        int l2=read();
        int len=read();
        int k=one[len];
        un(l1,l2,k);
        un(l1+len-(1<<k),l2+len-(1<<k),k);
    }

    for(int k=one[n];k>=1;k--){
        for(int i=1;i+(1<<k)-1<=n;i++){
            int fa=find(i,k);
            if(fa==i){
                continue;
            }
            un(i,fa,k-1);
            un(i+(1<<(k-1)),fa+(1<<(k-1)),k-1);
        }
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        if(find(i,0)==i){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}