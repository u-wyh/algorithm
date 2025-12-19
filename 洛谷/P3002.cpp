#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXH = 20;
const int INF = 1e9;

int len1,len2,n,m;
int s1[MAXN];
int s2[MAXN];
int s[MAXN];
char str[85];

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

int val[MAXN];

int tree[MAXN<<2];

void getsa(){
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

void buildst(){
    lg2[0]=-1;
    for(int i=1;i<=n;i++){
        lg2[i]=lg2[i>>1]+1;
    }
    for(int i=1;i<=n;i++){
        st[i][0]=height[i];
    }
    for(int i=1;i<=lg2[n];i++){
        for(int j=1;j+(1<<(i-1))-1<=n;j++){
            st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
        }
    }
}

int query(int l,int r){
    l++;
    int p=lg2[r-l+1];
    return min(st[l][p],st[r-(1<<p)+1][p]);
}

void compute(){
    int pre=0;
    for(int i=1;i<=n;i++){
        if(sa[i]<=len1){
            pre=i;
        }
        else if(sa[i]>len1+1){
            val[len1+len2+1+1-sa[i]]=query(pre,i);
        }
    }
    int suf=n;
    for(int i=n-1;i>=1;i--){
        if(sa[i]<=len1){
            suf=i;
        }
        else if(sa[i]>len1+1){
            val[len1+len2+1+1-sa[i]]=max(val[len1+len2+1+1-sa[i]],query(i,suf));
        }
    }
}

void up(int i){
    tree[i]=min(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    tree[i]=INF;
    if(l==r){
        return ;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=INF;
        if(jobl<=mid){
            ans=min(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

void solve(){
    build(1,len2,1);
    int res;
    for(int i=1;i<=len2;i++){
        res=0;
        if(val[i]==i){
            res=1;
        }
        else{
            res=query(i-val[i],i-1,1,len2,1)+1;
        }
        update(i,res,1,len2,1);
    }
    cout<<res<<endl;
}

void init(){
    scanf("%d %d",&len1,&len2);

    int now=0;
    while(true){
        scanf("%s",str+1);
        int len=strlen(str+1);
        for(int i=1;i<=len;i++){
            s1[++now]=str[i]-'A'+1;
        }
        if(now==len1){
            break;
        }
    }
    now=0;
    while(true){
        scanf("%s",str+1);
        int len=strlen(str+1);
        for(int i=1;i<=len;i++){
            s2[++now]=str[i]-'A'+1;
        }
        if(now==len2){
            break;
        }
    }

    m=27;
    for(int i=1;i<=len1;i++){
        s[++n]=s1[len1+1-i];
    }
    s[++n]=++m;
    for(int i=1;i<=len2;i++){
        s[++n]=s2[len2-i+1];
    }

    // for(int i=1;i<=n;i++){
    //     cout<<s[i]<<' ';
    // }
    // cout<<endl<<endl;
}

int main()
{
    init();
    getsa();
    getheight();
    buildst();
    compute();
    // for(int i=1;i<=len2;i++){
    //     cout<<val[i]<<' ';
    // }
    // cout<<endl;
    solve();
    return 0;
}