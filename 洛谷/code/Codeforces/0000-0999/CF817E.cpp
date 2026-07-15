#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN*28;
const int high = 28;

int q;
int cnt=1;
int tree[MAXT][2];
int pass[MAXT];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void add(int val){
    int cur=1;
    pass[cur]++;
    int path=0;
    for(int i=high;i>=0;i--){
        path=(val>>i)&1;
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
        pass[cur]++;
    }
}

void del(int val){
    int cur=1;
    pass[cur]--;
    int path=0;
    for(int i=high;i>=0;i--){
        path=(val>>i)&1;
        cur=tree[cur][path];
        pass[cur]--;
    }
}

int query(int val,int num){
    int ans=0;
    int cur=1;
    int path=0;
    int way=0;
    for(int i=high;i>=0;i--){
        path=(val>>i)&1;
        way=(num>>i)&1;
        if(way==1){
            ans+=pass[tree[cur][path]];
            cur=tree[cur][path^1];
        }
        else{
            cur=tree[cur][path];
        }
    }
    return ans;
}

int main()
{
    q=read();
    for(int i=1;i<=q;i++){
        int op,u,v;
        op=read(),u=read();
        if(op==3){
            v=read();
            printf("%d\n",query(u,v));
        }
        else if(op==1){
            add(u);
        }
        else if(op==2){
            del(u);
        }
    }
    return 0;
}