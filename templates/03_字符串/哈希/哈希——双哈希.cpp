//https://www.luogu.com.cn/problem/P5018  有点问题
//这道题的特别之处就是使用了双哈希
//并且通过不同的base来区别不同的遍历顺序
//并且左子树采用先序遍历  右子树采用后序遍历
//如果两棵子树是对称的  那么左树的先序和右树的后序应该是一样的、
//当然  不是严格的先序后序 只是先左边 后右边
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 1000001;
const int BASE1 = 499;
const int BASE2 = 1313;
const int BASE3 = 599;
const int BASE4 = 31;
const int BASE5 = 13131;
const int BASE6 = 433;
const int MOD1 = 1e9+7;
const int MOD2 = 88341364;

int n;
int lson[MAXN];
int rson[MAXN];
int sz[MAXN];
//双哈希函数数组
long long hl[MAXN];//先遍历左子树得到的哈希值  先序遍历
long long hr[MAXN];//先遍历右子树得到的哈希值  后序遍历
long long lh[MAXN];//先遍历左子树得到的哈希值
long long rh[MAXN];//先遍历右子树得到的哈希值
int arr[MAXN];
int ans=1;
int ans1;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void dfs(int u,int f){
    if(lson[u]){
        dfs(lson[u],u);
    }
    if(rson[u]){
        dfs(rson[u],u);
    }
    sz[u]=sz[lson[u]]+sz[rson[u]]+1;
    if(sz[lson[u]]==sz[rson[u]]&&hl[lson[u]]==hr[rson[u]]&&lh[lson[u]]==rh[rson[u]]){
        //双哈希函数判断
        ans=max(ans,sz[u]);
        if(sz[u]>=ans){
            ans1=u;
        }
    }
    //遍历顺序通过base体现
    hl[u]=hl[lson[u]]*BASE1+arr[u]*BASE2+hl[rson[u]]*BASE3;
    hr[u]=hr[rson[u]]*BASE1+arr[u]*BASE2+hr[lson[u]]*BASE3;
    hl[u]%=MOD1;
    hr[u]%=MOD1;

    lh[u]=lh[lson[u]]*BASE4+arr[u]*BASE5+lh[rson[u]]*BASE6;
    rh[u]=rh[rson[u]]*BASE4+arr[u]*BASE5+rh[lson[u]]*BASE6;
    lh[u]%=MOD2;
    rh[u]%=MOD2;
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    for(int i=1;i<=n;i++){
        int l,r;
        l=read(),r=read();
        if(l!=-1)
            lson[i]=l;
        if(r!=-1)
            rson[i]=r;
    }
    dfs(1,0);
    cout<<ans<<endl;
    return 0;
}