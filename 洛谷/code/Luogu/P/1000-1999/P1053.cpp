#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n;

int tot;
int target[MAXN];
int help[MAXN];
int cnt1[MAXN],cnt2[MAXN];

int son1[MAXN],son2[MAXN];

void dfs(int u,int f){
    if(u==1){
        return ;
    }
    target[++tot]=u;
    if(son1[u]==f){
        dfs(son2[u],u);
    }
    else{
        dfs(son1[u],u);
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>son1[i]>>son2[i];
        if(son1[i]<i){
            if(son1[son1[i]]!=i&&son2[son1[i]]!=i){
                cout<<-1<<endl;
                return 0;
            }
        }
        if(son2[i]<i){
            if(son1[son2[i]]!=i&&son2[son2[i]]!=i){
                cout<<-1<<endl;
                return 0;
            }
        }
    }
    target[++tot]=1;
    dfs(son1[1],1);
    for(int i=1;i<=n;i++){
        cnt1[(target[i]-i+n)%n]++;
    }
    tot=0;
    target[++tot]=1;
    dfs(son2[1],1);
    for(int i=1;i<=n;i++){
        cnt2[(target[i]-i+n)%n]++;
    }
    int ans=INT_MIN;
    for(int i=0;i<=n;i++){
        ans=max(ans,max(cnt1[i],cnt2[i]));
    }
    ans=n-ans;
    cout<<ans<<endl;
    return 0;
}