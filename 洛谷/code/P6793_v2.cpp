#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6e5+5;
const int MAXH = 20;

int n,m,k;
// 注意这里开的是二倍空间  这样可以减少很多判断语句
char str[MAXN];
int s[MAXN];
int id[MAXN];
// int len[MAXN];

int st[MAXN][MAXH];
int lg2[MAXN];

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

long long ans;

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

int compute(int l,int r){
    if(l==r){
        return id[sa[l]];
    }
    int mid=query(l,r);
    int lt=compute(l,mid-1);
    int rt=compute(mid,r);
    if(1ll*lt*rt>=0){
        return lt+rt;
    }
    if(lt<0&&rt>0){
        swap(lt,rt);
    }
    int t=min(lt,-rt);
    ans-=1ll*min(height[mid],k)*t;
    lt-=t;
    rt+=t;
    if(lt==0){
        return rt;
    }
    else{
        return lt;
    }
}

int main()
{
    cin>>n>>k;
    m=27;
    int tot=0;
    for(int i=1;i<=2;i++){
        scanf("%s",str+1);
        for(int j=1;j<=n;j++){
            s[++tot]=str[j]-'a'+1;
            if(n-j+1>=k){
                id[tot]=(i==1)?1:-1;
            }
        }
        s[++tot]=++m;
    }
    getsa(tot);
    getheight(tot);
    buildst(tot);
    ans=1ll*(n-k+1)*k;
    compute(1,tot);
    cout<<ans<<endl;
    return 0;
}