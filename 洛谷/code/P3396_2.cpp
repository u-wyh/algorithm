#include<bits/stdc++.h>
using namespace std;
const int MAXN = 150005;
const int MAXB = 405;

int n,m;
int val[MAXN];
int blen;
int sum[MAXB][MAXB];

void prepare(){
    blen=sqrt(n);
    for(int i=1;i<=blen;i++){
        for(int j=1;j<=n;j++){
            sum[i][j%i]+=val[j];
        }
    }
}

int query(int x,int y){
    if(x<=blen){
        return sum[x][y];
    }
    else{
        int ans=0;
        for(int i=y;i<=n;i+=x){
            ans+=val[i];
        }
        return ans;
    }
}

void update(int x,int y){
    int delta=y-val[x];
    val[x]=y;
    for(int i=1;i<=blen;i++){
        sum[i][x%i]+=delta;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
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