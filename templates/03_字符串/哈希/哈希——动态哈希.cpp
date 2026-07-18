// https://www.luogu.com.cn/problem/P10634
//动态哈希指的是哈希值并不能一开始就确定 需要随着变化不断调整
//一般都是维护一个区间  每次变化都是变化一个位置
//类似的题目还有P5256  不过这两个的技巧不一样
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 25005;
const int MAXK = 30;
const int BASE = 499;

int n,m,k;
int s[MAXN];//原始数组
int t[MAXM];//匹配数组

int cnt[MAXK];//每个数字出现次数
int rk[MAXK];//表示i这个数字在目前的cnt情况下的排名
int all[MAXK];//统计目前被统计的数字i所拥有的所有权值和

//用于统计答案
int ans[MAXN];
int len;

int p[MAXM];
int h[MAXN];

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

//初始化幂数组和哈希数组
void build(){
    p[0]=1;
    for(int i=1;i<=m;i++){
        p[i]=p[i-1]*BASE;
    }
    for(int i=1;i<=n;i++){
        h[i]=h[i-1]*BASE+s[i];
    }
}

//得到初始时l到r的哈希值
int gethash(int l,int r){
    return h[r]-h[l-1]*p[r-l+1];
}

//得到匹配数组的哈希值
int hashval(){
    int ans=rk[t[1]];
    for(int i=2;i<=m;i++){
        ans=ans*BASE+rk[t[i]];
    }
    return ans;
}

//根据目前的cnt数组  重置排名
void buildrank(){
    for(int i=1;i<=k;i++){
        rk[i]=0;
    }
    int rank=0;
    for(int i=1;i<=k;i++){
        if(cnt[i]){
            rk[i]=++rank;
        }
    }
}

//计算从l到r的真实哈希值
int rehash(int l,int r){
    int val=gethash(l,r);
    //减去每个数字被多估算的值  得到真实值
    for(int i=1;i<=k;i++){
        //在初始估算的时候  i的排名被算作为i  而实际上应该是c[i]  那么减去多算的即可
        val-=all[i]*(i-rk[i]);
    }
    return val;
}

signed main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++){
        s[i]=read();
    }
    for(int i=1;i<=m;i++){
        t[i]=read();
    }
    build();

    //准备离散化t   并得到他的哈希值
    for(int i=1;i<=m;i++){
        cnt[t[i]]++;
    }
    buildrank();
    int hasht=hashval();

    //将次数数组归零
    for(int i=1;i<=k;i++){
        cnt[i]=0;
    }

    //计算1~m的哈希值
    for(int i=1;i<=m;i++){
        cnt[s[i]]++;
        all[s[i]]+=p[m-i];//加上该位置的权值
    }
    buildrank();
    if(rehash(1,m)==hasht){
        ans[++len]=1;
    }

    //开始左移
    for(int i=m+1;i<=n;i++){
        // 更新元素计数
        cnt[s[i-m]]--;
        cnt[s[i]]++;

        buildrank();

        //更新数字的总权重
        for(int j=1;j<=k;j++){
            all[j]*=BASE;
        }

        all[s[i-m]]-=p[m];
        all[s[i]]+=p[0];

        if(rehash(i-m+1,i)==hasht){
            ans[++len]=i-m+1;
        }
    }

    cout<<len<<endl;
    for(int i=1;i<=len;i++){
        cout<<ans[i]<<endl;
    }

    return 0;
}