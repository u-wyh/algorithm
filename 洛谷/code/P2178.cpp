#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6e5+5;

int n,m;
// 注意这里开的是二倍空间  这样可以减少很多判断语句
char s[MAXN];
int val[MAXN];

//桶数组x[i] 辅助数组y[i] 计数数组c[i]
int x[MAXN];
int y[MAXN];
int c[MAXN];

// 后缀数组：排名第i的后缀的起始位置
int sa[MAXN];
// 排名数组：起始位置为i的后缀的排名
int rk[MAXN];
// height[i]表示的是排名为i和排名为i-1的最长公共前缀的长度
int height[MAXN];

int fa[MAXN];
int sz[MAXN];
int maxx[MAXN];
int minn[MAXN];

vector<int>vec[MAXN];

long long ans1;
long long ans2;

long long res1[MAXN];
long long res2[MAXN];

void getsa(){
    for(int i=1;i<=n;i++){
        x[i]=s[i]-'a'+1,c[x[i]]++;
    }
    for(int i=1;i<=m;i++){
        c[i]+=c[i-1];
    }
    for(int i=n;i>=1;i--){
        sa[c[x[i]]--]=i;
    }
    for(int k=1;k<=n;k<<=1){
        // 按照第二个关键字排序
        for(int i=0;i<=m;i++){
            c[i]=0;
        }
        for(int i=1;i<=n;i++){
            y[i]=sa[i];
        }
        for(int i=1;i<=n;i++){
            c[x[y[i]+k]]++;
        }
        for(int i=1;i<=m;i++){
            c[i]+=c[i-1];
        }
        for(int i=n;i>=1;i--){
            sa[c[x[y[i]+k]]--]=y[i];
        }

        // 按照第一个关键字排序
        for(int i=0;i<=m;i++){
            c[i]=0;
        }
        for(int i=1;i<=n;i++){
            y[i]=sa[i];
        }
        for(int i=1;i<=n;i++){
            c[x[y[i]]]++;
        }
        for(int i=1;i<=m;i++){
            c[i]+=c[i-1];
        }
        for(int i=n;i>=1;i--){
            sa[c[x[y[i]]]--]=y[i];
        }

        // 保存上一轮的组号到y数组
        for(int i=1;i<=n;i++){
            y[i]=x[i];
        }
        m=0;
        for(int i=1;i<=n;i++){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]){
                // 第一个关键字组号相同  第二个关键字组号相同  那么这一次也是一个组
                x[sa[i]]=m;
            }
            else{
                x[sa[i]]=++m;
            }
            if(m==n){
                break;
            }
        }
    }
}

void getheight(){
    for(int i=1;i<=n;i++){
        rk[sa[i]]=i;
    }
    for(int i=1,k=0;i<=n;i++){
        if(rk[i]==1){
            continue;
        }
        // 利用height性质：height[rk[i]] >= height[rk[i-1]] - 1
        if(k){
            k--;
        }
        int j=sa[rk[i]-1];
        while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]){
            k++;
        }
        height[rk[i]]=k;
    }
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void merge(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy){
        return ;
    }
    ans1+=1ll*sz[fx]*sz[fy];
    ans2=max(ans2,max(1ll*maxx[fx]*maxx[fy],1ll*minn[fx]*minn[fy]));
    fa[fx]=fy;
    sz[fy]+=sz[fx];
    maxx[fy]=max(maxx[fy],maxx[fx]);
    minn[fy]=min(minn[fy],minn[fx]);
}

int main()
{
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    m=27;
    getsa();
    getheight();
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
        maxx[i]=minn[i]=val[sa[i]];
        vec[height[i]].push_back(i);
    }
    ans2=LLONG_MIN;

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<(int)vec[i].size();j++){
            merge(vec[i][j],vec[i][j]-1);
        }
        if(ans1){
            res1[i]=ans1;
            res2[i]=ans2;
        }
    }
    for(int i=0;i<n;i++){
        cout<<res1[i]<<' '<<res2[i]<<endl;
    }
    return 0;
}