#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MOD = 998244353;

int n,m;

int tree1[MAXN];
int tree2[MAXN];

int op[MAXN];
int l[MAXN];
int r[MAXN];

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v,int op){
    if(op==1){
        while(x<=n){
            tree1[x]+=v;
            tree1[x]%=MOD;
            x+=lowbit(x);
        }
    }
    else{
        while(x<=m){
            tree2[x]+=v;
            tree2[x]%=MOD;
            x+=lowbit(x);
        }
    }
}

int sum(int x,int op){
    int ans=0;
    if(op==1){
        while(x){
            ans+=tree1[x];
            ans%=MOD;
            x-=lowbit(x);
        }
    }
    else{
        while(x){
            ans+=tree2[x];
            ans%=MOD;
            x-=lowbit(x);
        }
    }
    ans=(ans+MOD)%MOD;
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            tree1[i]=0;
        }
        for(int i=1;i<=m;i++){
            tree2[i]=0;
        }
        for(int i=1;i<=m;i++){
            op[i]=read();
            l[i]=read(),r[i]=read();
        }
        add(1,1,2);
        for(int i=m;i>=1;i--){
            int t=sum(i,2);
            if(op[i]==1){
                add(l[i],t,1);
                add(r[i]+1,-t,1);
            }
            else{
                add(l[i],t,2);
                add(r[i]+1,-t,2);
            }
        }
        cout<<sum(1,1);
        for(int i=2;i<=n;i++){
            cout<<' '<<sum(i,1);
        }
        cout<<endl;
    }
    return 0;
}