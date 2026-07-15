#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 1e6+5;

int n,m;
int maxval;
int val[MAXN];
char sign[MAXN];

int f[MAXN];
int pre[MAXN];
int tree1[MAXM];
int tree2[MAXM];
int eql[MAXM];

int anslen;
int endpos;

int lowbit(int x){
    return x&-x;
}

int calc(int x,int y){
    return f[x]>f[y]?x:y;
}

void update(int x,int val,int *tree){
    while(x<=maxval){
        tree[x]=calc(tree[x],val);
        x+=lowbit(x);
    }
}

int query(int x,int *tree){
    int ans=0;
    while(x){
        ans=calc(tree[x],ans);
        x-=lowbit(x);
    }
    return ans;
}

void compute(){
    for(int i=1;i<=n;i++){
        int best=eql[val[i]];

        best=calc(best,query(val[i]-1,tree1));
        best=calc(best,query(maxval-val[i],tree2));

        f[i]=f[best]+1;
        pre[i]=best;

        int nxtpos=(f[i]-1)%m+1;

        if(sign[nxtpos]=='<'){
            update(val[i],i,tree1);
        }
        else if(sign[nxtpos]=='='){
            eql[val[i]]=calc(eql[val[i]],i);
        }
        else{
            update(maxval-val[i]+1,i,tree2);
        }

        if(f[i]>anslen){
            anslen=f[i];
            endpos=i;
        }
    }
}

void dfs(int pos){
    if(pos){
        dfs(pre[pos]);
        cout<<val[pos]<<' ';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        maxval=max(maxval,val[i]);
    }
    for(int i=1;i<=m;i++){
        cin>>sign[i];
    }
    compute();
    cout<<anslen<<endl;
    dfs(endpos);
    return 0;
}