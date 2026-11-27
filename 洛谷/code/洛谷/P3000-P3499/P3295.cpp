// https://www.luogu.com.cn/problem/P3295
// 题意：
// 给定整数 n 和 m，
// 以及 m 组等长区间限制 (l1, r1, l2, r2)。
// 考虑长度为 n 的十进制大数 S_1 S_2 ...
// S_n（S_1 为最高位，不能为 0）。
// 每组限制要求子串 S[l1..r1] 与 S[l2..r2] 完全相同。
// 输出满足所有限制的大数个数，对 10^9 + 7 取模。
// 数据范围：
// 1 <= n <= 10^5
// 1 <= m <= 10^5
// 1 <= l_{i1}, r_{i1}, l_{i2}, r_{i2} <= n
// r_{i1} - l_{i1} = r_{i2} - l_{i2}
// 算法标签：并查集、ST表
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXH = 17;
const int MOD = 1e9+7;

int n,m;
int fa[MAXN][MAXH];
int one[MAXN];//记录数字i的二进制最高位1是哪一位

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
        int l1,r1,l2,r2;
        l1=read(),r1=read(),l2=read(),r2=read();
        int k=one[r1-l1+1];
        // 在k层上合并区间
        un(l1,l2,k);
        un(r1-(1<<k)+1,r2-(1<<k)+1,k);
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

    int cnt=0;
    for(int i=1;i<=n;i++){
        if(i==find(i,0)){
            cnt++;
        }
    }

    long long ans=9;
    for(int i=2;i<=cnt;i++){
        ans=(ans*10)%MOD;
    }

    cout<<ans<<endl;
    return 0;
}