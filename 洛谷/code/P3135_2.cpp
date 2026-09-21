// https://www.luogu.com.cn/problem/P3235
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int F;
int sg[MAXN];
int vis[MAXN];

int getval(int x,int v){
    int q=x/v;
    int r=x%v;

    int ans=0;
    if(r&1){
        ans^=sg[q+1];
    }
    if((v-r)&1){
        ans^=sg[q];
    }
    return ans;
}

void prepare(){
    for(int x=max(F,2);x<=100000;x++){
        for(int lt=2,rt;lt<=x;lt=rt+1){
            int v=x/lt;
            rt=x/v;
            int val=getval(x,lt);
            vis[val]=x;
            if(lt+1<=rt){
                val=getval(x,lt+1);
                vis[val]=x;
            }
        }
        int mex=0;
        while(vis[mex]==x){
            mex++;
        }
        sg[x]=mex;
    }
}

int main()
{
    int T;
    cin>>T>>F;
    prepare();
    for(int i=1;i<=T;i++){
        int eor=0;
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            int v;
            cin>>v;
            eor^=sg[v];
        }
        if(eor){
            cout<<1<<' ';
        }
        else{
            cout<<0<<' ';
        }
    }
    return 0;
}