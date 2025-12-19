// 使用后缀数组实现
#include<bits/stdc++.h>
using namespace std;
const int MAXL = 1e3+5;
const int MAXN = 2e6+2e3+5;

int n,m;
int len[MAXL];
int val[MAXL][MAXL];

int s[MAXN];
int id[MAXN];

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

int top;
int sta[MAXL];
bool vis[MAXL];

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

void getsa(int n){
    for(int i=1;i<=n;i++){
        x[i]=s[i],c[x[i]]++;
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

void getheight(int n){
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

bool check(int d,int n,int num){
    top=0;
    for(int i=1;i<=num;i++){
        vis[i]=false;
    }
    vis[0]=true;
    for(int i=1;i<=n;i++){
        if(height[i]<d){
            while(top){
                vis[sta[top--]]=false;
            }
        }
        int sub=id[sa[i]];
        if(!vis[sub]){
            vis[sub]=true;
            sta[++top]=sub;
            if(top==num){
                return true;
            }
        }
    }
    return false;
}

int main()
{
    n=read();
    m=5000;
    int tot=0;
    for(int i=1;i<=n;i++){
        len[i]=read();
        for(int j=1;j<=len[i];j++){
            val[i][j]=read();
        }
        for(int j=1;j<len[i];j++){
            s[++tot]=val[i][j+1]-val[i][j];
            id[tot]=i;
        }
        s[++tot]=++m; 
    }
    getsa(tot);
    getheight(tot);

    // for(int i=1;i<=tot;i++){
    //     cout<<s[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=1;i<=tot;i++){
    //     cout<<i<<":  "<<sa[i]<<endl;
    // }
    // cout<<endl;
    // for(int i=1;i<=tot;i++){
    //     cout<<i<<":  "<<height[i]<<endl;
    // }
    // cout<<endl;

    int l=1,r=1000,ans=0;
    for(int i=1;i<=n;i++){
        r=min(r,len[i]-1);
    }
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid,tot,n)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<(ans+1)<<endl;
    return 0;
}