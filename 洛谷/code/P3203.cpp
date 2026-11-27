// https://www.luogu.com.cn/problem/P3203
// 题意：输入弹力装置数量 n（编号 0 到 n-1）、各装置初始弹力系数 k_i，以及操作数 m 和 m 次操作。
// 绵羊落到第 j 个装置会跳到 j + k_j，若下标 >= n 则被弹飞；
// 操作 1 查询从 j 出发需弹几次被弹飞，操作 2 将装置 j 的系数修改为 k。
// 对每次查询操作输出一行弹飞所需步数。
// 数据范围：1 <= n <= 2*10^5，1 <= m <= 10^5，弹力系数均为正整数。
#include<bits/stdc++.h>
// 算法标签：分块
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 1e3+5;

int n,m;
int nums[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int f[MAXN];
int g[MAXN];

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

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    for(int i=n;i>=1;i--){
        int nxt=i+nums[i];
        if(nxt>n){
            f[i]=1;
            g[i]=n+1;
        }
        else if(nxt>br[bi[i]]){
            f[i]=1;
            g[i]=nxt;
        }
        else{
            f[i]=f[nxt]+1;
            g[i]=g[nxt];
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    m=read();
    while(m--){
        int op,pos,val;
        op=read(),pos=read();
        pos++;
        if(op==1){
            int ans=0;
            while(pos<=n){
                ans+=f[pos];
                pos=g[pos];
            }
            printf("%d\n",ans);
        }
        else{
            val=read();
            nums[pos]=val;
            for(int i=br[bi[pos]];i>=bl[bi[pos]];i--){
                int nxt=i+nums[i];
                if(nxt>n){
                    f[i]=1;
                    g[i]=n+1;
                }
                else if(nxt>br[bi[i]]){
                    f[i]=1;
                    g[i]=nxt;
                }
                else{
                    f[i]=f[nxt]+1;
                    g[i]=g[nxt];
                }
            }
        }
    }
    return 0;
}