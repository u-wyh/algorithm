#include<bits/stdc++.h>
using namespace std;
const int MAXN = 8e5+5;
const int MAXH = 22;

int n,m;
long long ans;
char s1[MAXN];
char s2[MAXN];
int s[MAXN];

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

int lg2[MAXN];
int st[MAXN][MAXH];

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

void buildst(int n){
    lg2[0]=-1;
    for(int i=1;i<=n;i++){
        lg2[i]=lg2[i>>1]+1;
    }
    for(int i=1;i<=n;i++){
        st[i][0]=i;
    }
    for(int i=1;i<=lg2[n];i++){
        for(int j=1;j+(1<<(i-1))-1<=n;j++){
            if(height[st[j][i-1]]<height[st[j+(1<<(i-1))][i-1]]){
                st[j][i]=st[j][i-1];
            }
            else{
                st[j][i]=st[j+(1<<(i-1))][i-1];
            }
        }
    }
}

int query(int l,int r){
    l++;
    int p=lg2[r-l+1];
    if(height[st[l][p]]<height[st[r-(1<<p)+1][p]]){
        return st[l][p];
    }
    else{
        return st[r-(1<<p)+1][p];
    }
}

long long compute(int l,int r){
    // cout<<l<<' '<<r<<endl;
    if(l==r){
        return 0;
    }
    int mid=query(l,r);
    int val=height[mid];
    long long ans=1ll*val*(mid-l)*(r-mid+1);
    ans+=compute(l,mid-1);
    ans+=compute(mid,r);
    return ans;
}

int main()
{
    scanf("%s",s1+1);
    scanf("%s",s2+1);
    int len1=strlen(s1+1);
    int len2=strlen(s2+1);

    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    memset(c,0,sizeof(c));
    memset(sa,0,sizeof(sa));
    memset(rk,0,sizeof(rk));
    memset(height,0,sizeof(height));
    for(int i=1;i<=len1;i++){
        s[i]=s1[i]-'a'+1;
    }
    m=27;
    getsa(len1);
    getheight(len1);
    buildst(len1);
    ans-=compute(1,len1);

    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    memset(c,0,sizeof(c));
    memset(sa,0,sizeof(sa));
    memset(rk,0,sizeof(rk));
    memset(height,0,sizeof(height));
    for(int i=1;i<=len2;i++){
        s[i]=s2[i]-'a'+1;
    }
    m=27;
    getsa(len2);
    getheight(len2);
    buildst(len2);
    ans-=compute(1,len2);

    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    memset(c,0,sizeof(c));
    memset(sa,0,sizeof(sa));
    memset(rk,0,sizeof(rk));
    memset(height,0,sizeof(height));
    for(int i=1;i<=len1;i++){
        s[i]=s1[i]-'a'+1;
    }
    s1[++len1]=++m;
    for(int i=1;i<=len2;i++){
        s[i+len1]=s2[i]-'a'+1;
    }
    m=27;
    getsa(len1+len2);
    getheight(len1+len2);
    buildst(len1+len2);
    ans+=compute(1,len1+len2);

    cout<<ans<<endl;
    return 0;
}