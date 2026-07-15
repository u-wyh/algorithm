#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;
const int MAXM = 5e6+5;

int n,m,q;
string str;
int s[MAXN];
int pre[MAXN+MAXM];
int p[MAXM];
int h[MAXM];

int fa[MAXN];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void prepare(){
    for(int i=1;i<=n*m;i++){
        s[i]=str[i-1]-'0';
    }
    for(int i=1;i<=m+1;i++){
        fa[i]=i;
        p[i]=1ll*rand()*rand();
    }
    for(int i=1;i<=n;i++){
        int l=(i-1)*m+1,r=i*m;
        int lt=(i-1)*(m+1)+1,rt=i*(m+1);
        pre[lt]=s[l];
        for(int j=1;j<m;j++){
            pre[lt+j]=s[l+j-1]^s[l+j];
        }
        pre[rt]=s[r];

        for(int j=1;j<=m+1;j++){
            h[i]+=p[j]*pre[lt+j-1];
        }
    }
}

void compute(int x,int y){
    y++;
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        for(int i=1;i<=n;i++){
            int st=(i-1)*(m+1);
            int oldx=pre[st+fx];
            int oldy=pre[st+fy];
            h[i]-=p[fx]*oldx;
            h[i]-=p[fy]*oldy;

            fa[fx]=fy;
            p[fy]+=p[fx];
            pre[st+fy]^=pre[st+fx];

            h[i]+=p[fy]*pre[st+fy];
        }
    }
}

signed main()
{   
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0));

    cin>>n>>m>>q;
    cin>>str;

    prepare();

    for(int i=1;i<=q;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            compute(x,y);
        }
        else{
            if(h[x]!=h[y]){
                cout<<"Haru"<<endl;
            }
            else{
                cout<<"Masuko"<<endl;
            }
        }
    }
    return 0;
}