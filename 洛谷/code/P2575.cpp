// https://www.luogu.com.cn/problem/P2575
#include<bits/stdc++.h>
using namespace std;
const int MAXN = (1<<20)+5;

int sg[MAXN];
bool vis[25];

void prepare(){
    int N=(1<<20)-1;
    for(int i=N;i>=0;i--){
        for(int v=0;v<=24;v++){
            vis[v]=false;
        }
        for(int j=0;j<=19;j++){
            if(((i>>j)&1)){
                int k=j+1;
                for(;k<=19;k++){
                    if(!((i>>k)&1)){
                        int nxt=i-(1<<j)+(1<<k);
                        vis[sg[nxt]]=true;
                        break;
                    }
                }
            }
        }

        int mex=0;
        while(vis[mex]){
            mex++;
        }
        sg[i]=mex;
    }
}

int main()
{
    prepare();
    int T;
    cin>>T;
    while(T--){
        int eor=0;
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            int m;
            cin>>m;
            int sta=0;
            for(int j=1;j<=m;j++){
                int v;
                cin>>v;
                v--;
                sta|=(1<<v);
            }
            eor^=sg[sta];
        }
        if(eor){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}