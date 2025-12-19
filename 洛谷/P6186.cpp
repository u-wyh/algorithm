#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m;
int arr[MAXN];
int f[MAXN];
int tree[MAXN];
int tree1[MAXN];
int tree2[MAXN];

int lowbit(int i){
    return i&(-i);
}

int sum(int x,int *tree){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void add(int x,int val,int *tree){
    if(x==0){
        return ;
    }
    while(x<=n){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        f[i]=sum(n,tree)-sum(arr[i],tree);
        if(arr[i]==n){
            f[i]=0;
        }
        add(arr[i],1,tree);
    }
    for(int i=1;i<=n;i++){
        add(f[i],1,tree1);
        add(f[i],f[i],tree2);
    }
    //cout<<666<<endl;
    for(int i=1;i<=m;i++){
        int op,u;
        cin>>op>>u;
        if(op==1){
            if(arr[u]>arr[u+1]){
                add(f[u],-1,tree1);
                add(f[u+1],-1,tree1);
                add(f[u],-f[u],tree2);
                add(f[u+1],-f[u+1],tree2);
                swap(f[u],f[u+1]);
                f[u]--;
                add(f[u],1,tree1);
                add(f[u+1],1,tree1);
                add(f[u],f[u],tree2);
                add(f[u+1],f[u+1],tree2);
                swap(arr[u],arr[u+1]);
            }
            else if(arr[u]<arr[u+1]){
                add(f[u],-1,tree1);
                add(f[u+1],-1,tree1);
                add(f[u],-f[u],tree2);
                add(f[u+1],-f[u+1],tree2);
                swap(f[u],f[u+1]);
                f[u+1]++;
                add(f[u],1,tree1);
                add(f[u+1],1,tree1);
                add(f[u],f[u],tree2);
                add(f[u+1],f[u+1],tree2);
                swap(arr[u],arr[u+1]);
            }
        }
        else{
            if(u>=n-1){
                cout<<0<<endl;
                continue;
            }
            int ans=sum(n,tree2)-sum(u,tree2);
            ans-=u*(sum(n,tree1)-sum(u,tree1));
            cout<<ans<<endl;
        }
    }
    return 0;
}
