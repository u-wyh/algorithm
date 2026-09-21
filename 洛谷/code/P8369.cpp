// https://www.luogu.com.cn/problem/P8369
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
int length[3];
int sg[MAXN];
int val[MAXN];
bool vis[MAXN];
int maxv;

void prepare(){
    sg[0]=0;
    for(int i=1;i<=maxv;i++){
        for(int v=0;v<=maxv;v++){
            vis[v]=false;
        }
        for(int l=0;l<=2;l++){
            int len=length[l];
            for(int lt=0;lt<=i-len;lt++){
                int rt=i-len-lt;
                if(rt>=0){
                    vis[sg[lt]^sg[rt]]=true;
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
    cin>>length[0]>>length[1]>>length[2];
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        maxv=max(maxv,val[i]);
    }
    prepare();
    for(int i=1;i<=n;i++){
        if(sg[val[i]]){
            cout<<1<<endl;
        }
        else{
            cout<<2<<endl;
        }
    }
    return 0;
}