#include<bits/stdc++.h>
using namespace std;
const int MAXN = 150005;
const int MAXB = 405;

int n,m;
int nums[MAXN];
int blen;
long long f[MAXB][MAXB];

void prepare(){
    blen=sqrt(n);
    for(int x=1;x<=blen;x++){
        for(int i=1;i<=n;i++){
            f[x][i%x]+=nums[i];
        }
    }
}

int query(int x,int y){
    if(x<=blen){
        return f[x][y];
    }
    else{
        long long ans=0;
        for(int i=y;i<=n;i+=x){
            ans+=nums[i];
        }
        return ans;
    }
}

void update(int x,int y){
    int delta=y-nums[x];
    nums[x]=y;
    for(int i=1;i<=blen;i++){
        f[i][x%i]+=delta;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    prepare();
    for(int i=1;i<=m;i++){
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='A'){
            cout<<query(x,y)<<endl;
        }
        else{
            update(x,y);
        }
    }
    return 0;
}