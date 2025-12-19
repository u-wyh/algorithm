#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n,m,ans;
int a[MAXN][MAXN];
int b[MAXN][MAXN];

int f[MAXN];

map<int,int>mp;

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

int tree[MAXN];

int lowbit(int x){
    return x&-x;
}

void update(int x,int val){
    while(x<=m){
        tree[x]=max(val,tree[x]);
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

int compute(int *a,int *b){
    int cnt=0;
    for(int i=1;i<=m;i++){
        if(a[i]!=0){
            cnt++;
        }
    }
    int u=0;
    for(int i=1;i<=m;i++){
        if(b[i]!=0){
            mp[b[i]]=++u;
        }
    }
    for(int i=1;i<=m;i++){
        if(a[i]!=0){
            a[i]=mp[a[i]];
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        tree[i]=f[i]=0;
    }
    for(int i=1;i<=m;i++){
        if(a[i]){
            f[i]=query(a[i]-1)+1;
            update(a[i],f[i]);
            ans=max(f[i],ans);
        }
    }
    if(cnt-ans==0){
        return 0;
    }
    return cnt-ans+((cnt==m)?1:0);
}

int main() {
    n=read(),m=read();
    bool flag=false;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            a[i][j]=read();
            if(a[i][j]==0){
                flag=true;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            b[i][j]=read();
        }
    }
    bool ok=false;
    if(!flag){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i][j]!=b[i][j]){
                    ok=1;
                    break;
                }
            }
            if(ok){
                break;
            }
        }
    }
    if(!flag&&ok){
        cout<<-1<<endl;
        return 0;
    }
    else if(!flag&&!ok){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=n;i++){
        ans+=compute(a[i],b[i]);
    }
    cout<<ans<<endl;
    return 0;
}