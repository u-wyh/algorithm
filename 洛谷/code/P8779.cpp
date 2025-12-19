#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+6;
int fa[N],sum[N];
int n,m,q;
int l,r,s;
int find(int x){
    if(fa[x]==x)return x;
    int root=find(fa[x]);
    sum[x]+=sum[fa[x]];
    fa[x]=root;
    return fa[x];
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        cin>>l>>r>>s;
        l--;
        int fl=find(l),fr=find(r);
        if(fl!=fr){
            fa[fl]=fr;
            sum[fl]=-s-sum[l]+sum[r];
        }
    }
    for(int i=1;i<=q;i++){
        cin>>l>>r;
        l--;
        int fl=find(l),fr=find(r);
        if(fl!=fr){
            cout<<"UNKNOWN"<<'\n';
            continue;
        }
        cout<<sum[r]-sum[l]<<'\n';
    }
    return 0;
}
