#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
char s[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int nums[MAXN][26];

void prepare(){
    cnt=1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        for(int j=0;j<26;j++){
            nums[i][j]=0;
        }
    }
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        prepare();
        scanf("%s",s+1);
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            addedge(u,v);
            addedge(v,u);
        }
        for(int u=1;u<=n;u++){
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                nums[u][s[v]-'A']++;
            }
        }
        long long ans=0;
        for(int u=1;u<=n;u++){
            if(s[u]!='C'){
                continue;
            }
            int lt=0,rt=0;
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                if(s[v]=='C'){
                    lt+=nums[v][18];
                }
                if(s[v]=='P'){
                    rt+=nums[v][2]-1;
                }
            }
            ans+=1ll*lt*rt;
        }
        cout<<ans<<endl;
    }
    return 0;
}