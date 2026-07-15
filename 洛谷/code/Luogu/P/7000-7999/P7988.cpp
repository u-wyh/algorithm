#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int val[MAXN];

int ls[MAXN];
int rs[MAXN];
int st[MAXN];
int sta[MAXN];
int cnt[MAXN];

int ans[MAXN];

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

void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

void build(){
    int top=0;
    for(int i=1;i<=n;i++){
        int pos=top;
        while(pos>0&&val[st[pos]]>val[i]){
            pos--;
        }
        if(pos>0){
            rs[st[pos]]=i;
        }
        if(pos<top){
            ls[i]=st[pos+1];
        }
        st[++pos]=i;
        top=pos;
    }
}

void dfs(int u,int fa){
    // cout<<u<<' '<<fa<<' '<<sta[u]<<endl;
    cnt[u]=cnt[fa]+(sta[fa]==1&&sta[u]==0);
    // cout<<u<<":   "<<cnt[u]<<endl;
    if(ls[u]){
        sta[ls[u]]=1;
        dfs(ls[u],u);
    }
    else{
        ans[u-1]=cnt[u];
        // cout<<u<<' '<<u-1<<endl;
    }
    if(rs[u]){
        sta[rs[u]]=0;
        dfs(rs[u],u);
    }
    else{
        ans[u]=cnt[u]+(sta[u]==1);
        // cout<<u<<' '<<u<<endl;
    }
}

int main()
{
    n=read();
    int root=0;
    for(int i=1;i<=n;i++){
        int k=read();
        val[k]=i;
        if(i==1){
            root=k;
        }
    }
    build();
    dfs(root,0);
    for(int i=0;i<=n;i++){
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}