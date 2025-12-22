#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MAXH = 22;
const int MOD = 23333333333333333;
const int MAXM = 3e6+5;

int n,t,m;
// 注意这里开的是二倍空间  这样可以减少很多判断语句
char s[MAXN];

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

int lg2[MAXN];
int st[MAXN][MAXH];

void buildst(){
    lg2[0]=-1;
    for(int i=1;i<=n;i++){
        lg2[i]=lg2[i>>1]+1;
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
    int p=lg2[r-l+1];
    if(height[st[l][p]]<height[st[r-(1<<p)+1][p]]){
        return st[l][p];
    }
    else{
        return st[r-(1<<p)+1][p];
    }
}

int k;
int arr[MAXM];
int ans;
bool vis[MAXN];

bool cmp(int a,int b){
    return a<b;
}

int find(int val){
    int l=1,r=k,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]<=val){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans;
}

// 处理在arr数组中排名为lt~rt的答案
void fun(int lt,int rt){
    // cout<<"   "<<lt<<' '<<rt<<endl;
    if(rt<=lt){
        return ;
    }

    int split=query(arr[lt]+1,arr[rt]);
    int pos=find(split);

    int l=pos-lt+1;
    int r=rt-pos;

    int val=height[split];

    if(vis[split]){
        ans=(ans+((l-1)*(r+1)%MOD)*val)%MOD;
        fun(lt,pos-1);
        fun(pos,rt);
    }
    else{
        ans=(ans+(l*r%MOD)*val)%MOD;
        fun(lt,pos);
        fun(pos+1,rt);
    }
}

void compute(){
    sort(arr+1,arr+k+1,cmp);
    m=1;
    for(int i=2;i<=k;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    k=m;
    if(k==1){
        cout<<0<<endl;
        return ;
    }

    // cout<<"   "<<k<<endl;
    for(int i=1;i<=k;i++){
        vis[arr[i]]=true;
    }
    ans=0;
    fun(1,k);
    for(int i=1;i<=k;i++){
        vis[arr[i]]=false;
    }
    cout<<ans<<endl;
    return ;
}

signed main()
{
    scanf("%d %d",&n,&t);
    m=26;
    scanf("%s",s+1);
    getsa();
    getheight();

    // for(int i=1;i<=n;i++){
    //     cout<<sa[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<rk[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<height[i]<<' ';
    // }
    // cout<<endl;

    buildst();
    for(int i=1;i<=t;i++){
        scanf("%d",&k);
        for(int i=1;i<=k;i++){
            scanf("%d",&arr[i]);
            arr[i]=rk[arr[i]];
        }
        if(k==1){
            cout<<0<<endl;
            continue;
        }
        compute();
    }
    return 0;
}
/*
8 1
abccabab
4 2 3 4 5
*/