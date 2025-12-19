#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
int val[MAXN];
char s[MAXN];

int tree[2][MAXN];

inline int lowbit(int x){
    return x&-x;
}

void update(int op,int x,int val){
    while(x<=n){
        tree[op][x]=max(tree[op][x],val);
        x+=lowbit(x);
    }
}

int query(int op,int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[op][x]);
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    scanf("%s",s+1);
    
    int ans=0;
    for(int i=1;i<=n;i++){
        int res=max(query(0,val[i]),query(1,n-val[i]));
        ans=max(ans,res);

        if(s[res+1]=='U'){
            update(0,val[i],res+1);
        }
        else{
            update(1,n-val[i]+1,res+1);
        }
    }

    cout<<ans<<endl;
    return 0;
}