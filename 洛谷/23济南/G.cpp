#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

char s[MAXN];
int fa[MAXN<<1];
// bool vis[MAXN<<1];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    // cout<<ans<<endl;
    return ans;
}

signed main()
{
    int T;
    scanf("%lld",&T);
    while(T--){
        int n,m;
        cin>>n>>m;
        vector<vector<int>>vec(n,vector<int>(m,0));
        vector<vector<int>>col(m);
        for(int i=0;i<n;i++){
            scanf("%s",s);
            for(int j=0;j<m;j++){
                vec[i][j]=s[j]-'0';
                if(s[j]=='1'){
                    col[j].push_back(i);
                }
            }
        }
        bool flag=false;
        for(int i=0;i<m;i++){
            if((col[i].size()+col[m-1-i].size())>2){
                flag=true;
                break;
            }
            // else if(col[i].size()>2&&(2*i==(m-1))){
            //     flag=true;
            //     break;
            // }
        }
        if(flag){
            cout<<0<<endl;
            continue;
        }

        for(int i=0;i<n;i++){
            fa[i]=i;
            fa[i+n]=i+n;
        }

        for(int i=0;i<m;i++){
            int sz1=col[i].size();
            int sz2=col[m-i-1].size();
            // if(2*i==(m-1)){
            //     if(sz1==2){
            //         int x=col[i][0];
            //         int y=col[i][1];
            //         un(x,y+n);
            //         un(x+n,y);
            //     }
            // }
            // else{
                if(sz1+sz2==1){
                    continue;
                }
                else{
                    if(sz1){
                        if(sz2==0){
                            int x=col[i][0];
                            int y=col[i][1];
                            un(x+n,y);
                            un(x,y+n);
                        }
                        else{
                            int x=col[i][0];
                            int y=col[m-i-1][0];
                            un(x,y);
                            un(x+n,y+n);
                        }
                    }
                }
            // }
        }

        int all=0;
        for(int i=0;i<2*n;i++){
            if(i==find(i)){
                all++;
            }
            if(find(i)==find(i+n)){
                flag=true;
                break;
            }
        }

        if(flag){
            // cout<<888<<endl;
            cout<<0<<endl;
        }
        else{
            cout<<power(2,all/2)<<endl;
        }
    }
    return 0;
}