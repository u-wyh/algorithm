#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n,m;
int val[MAXN];

int root;
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];

int ans1;
long long ans2;

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

void build() {
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int pos = top;

        while (pos > 0 && val[sta[pos]] > val[i]) {
            pos--;
        }

        if (pos > 0) {
            rs[sta[pos]] = i;
        }

        if (pos < top) {
            ls[i] = sta[pos + 1];
        }

        sta[++pos] = i;//加入栈中
        top = pos;
    }
    root=sta[1];
}

int gcd(int a,int b){
    if(a<b){
        swap(a,b);
    }
    return b==0?a:gcd(b,a%b);
}

bool dfs(int u,int x){
    if(ls[u]){
        if((val[ls[u]]+x)%(val[u]+x)!=0){
            return false;
        }
    }
    if(rs[u]){
        if((val[rs[u]]+x)%(val[u]+x)!=0){
            return false;
        }
    }
    if(ls[u]){
        if(!dfs(ls[u],x)){
            return false;
        }
    }
    if(rs[u]){
        if(!dfs(rs[u],x)){
            return false;
        }
    }
    return true;
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        ans1=0,ans2=0;
        for(int i=1;i<=n;i++){
            val[i]=read();
        }

        if(n==1){
            cout<<m<<' '<<(1ll*m*(m+1)/2)<<endl;
            continue;
        }
        for(int i=1;i<=n;i++){
            ls[i]=0,rs[i]=0;
        }
        build();

        int res=0;
        for(int i=1;i<n;i++){
            res=gcd(abs(val[i]-val[i+1]),res);
        }
        // cout<<res<<endl;

        // cout<<root<<endl;
        // for(int i=1;i<=n;i++){
        //     cout<<i<<":   "<<ls[i]<<' '<<rs[i]<<endl;
        // }
        // cout<<endl;

        for(int i=1;1ll*i*i<=res;i++){
            if((i>val[root])&&dfs(root,i-val[root])){
                ans1++;
                ans2+=i-val[root];
            }
            if(i!=res/i){
                if((res/i-val[root]>0)&&dfs(root,res/i-val[root])){
                    ans1++;
                    ans2+=res/i-val[root];
                }
            }
        }

        cout<<ans1<<' '<<ans2<<endl;
    }
    return 0;
}