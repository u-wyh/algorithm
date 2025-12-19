#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+500;
const int MAXM = 55;

int n,m;
char str[MAXN];
// 注意这里开的是二倍空间  这样可以减少很多判断语句
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

int ans[MAXM][MAXM];
int minn[MAXM];

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

int main()
{
    m=27;
    int tot=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",str+1);
        int len=strlen(str+1);
        for(int j=1;j<=len;j++){
            s[++tot]=str[j]-'a'+1;
            id[tot]=i;
        }
        s[++tot]=++m;
    }
    getsa(tot);
    getheight(tot);

    // for(int i=1;i<=tot;i++){
    //     cout<<i<<":   "<<height[i]<<' '<<sa[i]<<endl;
    // }
    // cout<<endl;

    // for(int i=1;i<=n;i++){
    //     minn[i]=INT_MAX;
    // }
    for(int i=2;i<=tot;i++){
        for(int j=1;j<=n;j++){
            minn[j]=min(minn[j],height[i]);
        }
        minn[id[sa[i-1]]]=height[i];

        int now=id[sa[i]];

        // for(int j=1;j<=n;j++){
        //     cout<<minn[j]<<' ';
        // }
        // cout<<now;
        // cout<<endl;

        for(int j=1;j<=n;j++){
            ans[now][j]=max(ans[now][j],minn[j]);
            ans[j][now]=max(ans[j][now],minn[j]);
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j){
                cout<<ans[i][j]<<' ';
            }
        }
        cout<<endl;
    }
    return 0;
}