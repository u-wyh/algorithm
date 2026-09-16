// https://www.luogu.com.cn/problem/P9358
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 320;

int n,m,q;

int blen;
int bnum;
int bl[MAXB];
int br[MAXB];
int bi[MAXN];

int to[MAXB][MAXN];

map<int,int>bridge[MAXN];

void prepare(){
    blen=max(1,(int)sqrt(m));
    bnum=(m+blen-1)/blen;
    for(int i=1;i<=m;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(m,i*blen);
    }

    for(int i=1;i<=bnum;i++){
        for(int j=1;j<=n;j++){
            to[i][j]=j;
        }
    }
}

void addbridge(int a,int b){
    int id=bi[b];
    int x=a;
    int y=a+1;
    for(int j=b-1;j>=bl[id];j--){
        auto it=bridge[x].find(j);
        if(it!=bridge[x].end()){
            x=it->second;
        }

        it=bridge[y].find(j);
        if(it!=bridge[y].end()){
            y=it->second;
        }
    }
    swap(to[id][x],to[id][y]);
    bridge[a][b]=a+1;
    bridge[a+1][b]=a;
}

int query(int x){
    for(int i=1;i<=bnum;i++){
        x=to[i][x];
    }
    return x;
}

int main()
{
    cin>>n>>m>>q;
    prepare();
    for(int i=1;i<=q;i++){
        int op,a,b;
        cin>>op>>a;
        if(op==1){
            cin>>b;
            addbridge(a,b);
        }
        else{
            cout<<query(a)<<endl;
        }
    }
    return 0;
}