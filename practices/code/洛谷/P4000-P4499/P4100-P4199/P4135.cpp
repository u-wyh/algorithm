// https://www.luogu.com.cn/problem/P4135
// 题意：强制在线。
// 第一行输入长度 n、值域上界 c 和询问数 m；
// 第二行输入数列 a_1..a_n；
// 接下来 m 行每行输入加密的 L,
// R（由上一问答案 ans 解密得 [l, r]）。
// 每次询问区间 [l, r] 中出现正偶数次的数的种类数。
// 输出 m 行，每行一个整数表示答案。
// 数据范围：1 <= n, c, m <= 10^5，1 <= a_i <= c，
// 1 <= l, r <= n。
// 难度评分：2500（洛谷分级换算）
// 算法标签：分块、前缀和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,c,m;
int nums[MAXN];

int blen;
int bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int freq[MAXB][MAXN];
int even[MAXB][MAXB];
int cnt[MAXN];

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

int getcnt(int l,int r,int v){
    return freq[r][v]-freq[l-1][v];
}

int delta(int pre){
    if(pre==0){
        return 0;
    }
    if(pre&1){
        return 1;
    }
    return -1;
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
    for(int i=1;i<=bnum;i++){
        for(int j=bl[i];j<=br[i];j++){
            freq[i][nums[j]]++;
        }
        for(int j=1;j<=c;j++){
            freq[i][j]+=freq[i-1][j];
        }
    }
    for(int i=1;i<=bnum;i++){
        for(int j=i;j<=bnum;j++){
            even[i][j]=even[i][j-1];
            for(int k=bl[j];k<=br[j];k++){
                even[i][j]+=delta(cnt[nums[k]]++);
            }
        }
        for(int j=1;j<=c;j++){
            cnt[j]=0;
        }
    }
}

int query(int l,int r){
    int ans=0;
    if(bi[l]==bi[r]){
        for(int i=l;i<=r;i++){
            ans+=delta(cnt[nums[i]]++);
        }
        for(int i=l;i<=r;i++){
            cnt[nums[i]]=0;
        }
    }
    else{
        ans=even[bi[l]+1][bi[r]-1];
        for(int i=l;i<=br[bi[l]];i++){
            ans+=delta(getcnt(bi[l]+1,bi[r]-1,nums[i])+cnt[nums[i]]);
            cnt[nums[i]]++;
        }
        for(int i=bl[bi[r]];i<=r;i++){
            ans+=delta(getcnt(bi[l]+1,bi[r]-1,nums[i])+cnt[nums[i]]);
            cnt[nums[i]]++;
        }
        for(int i=l;i<=br[bi[l]];i++){
            cnt[nums[i]]=0;
        }
        for(int i=bl[bi[r]];i<=r;i++){
            cnt[nums[i]]=0;
        }
    }
    return ans;
}

int main()
{
    n=read(),c=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    int ans=0;
    for(int i=1;i<=m;i++){
        int l,r;
        l=read(),r=read();
        l=(l+ans)%n+1;
        r=(r+ans)%n+1;
        if(l>r){
            swap(l,r);
        }
        ans=query(l,r);
        printf("%d\n",ans);
    }
    return 0;
}