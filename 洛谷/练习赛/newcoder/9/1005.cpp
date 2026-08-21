#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int val[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];

int dep[MAXN];
int nxt[MAXN];
int ans[MAXN];

void build(){
    int top=0;
    for(int i=1;i<=n;i++){
        int pos=top;
        while(pos>0&&val[sta[pos]]>val[i]){
            pos--;
        }

        if(pos>0){
            rs[sta[pos]]=i;
        }

        if(pos<top){
            ls[i]=sta[pos+1];
        }

        if(pos){
            nxt[i]=i-sta[pos];
        }
        else{
            nxt[i]=i;
        }

        sta[++pos]=i;
        top=pos;
    }
}

int q[MAXN];
void dfs(){
    dep[sta[1]]=1;
    int l=1,r=0;
    q[++r]=sta[1];
    while(l<=r){
        int u=q[l++];
        if(ls[u]){
            dep[ls[u]]=dep[u]+1;
            q[++r]=ls[u];
        }
        if(rs[u]){
            dep[rs[u]]=dep[u]+1;
            q[++r]=rs[u];
        }
    }
}

bool check(int i,int j){
    if(nxt[i]==i&&nxt[j]>=i){
        return true;
    }
    return nxt[i]==nxt[j];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>val[i];
            ls[i]=rs[i]=0;
        }
        
        build();

        // for(int i=1;i<=n;i++){
        //     cout<<ls[i]<<' '<<rs[i]<<endl;
        // }
        // cout<<sta[1]<<endl;

        dfs();

        ans[1]=0;
        for(int i=2;i<=n;i++){
            int u=ans[i-1];
            while(u!=0&&!check(u+1,i)){
                u=ans[u];
            }
            if(check(u+1,i)){
                u++;
            }
            ans[i]=u;
        }

        for(int i=1;i<=n;i++){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
/*
1
2
1 1

1
5
2 1 3 1 2

*/