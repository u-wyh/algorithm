#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int val[MAXN];
int tmp[MAXN];
int pos[MAXN];
int vis[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>val[i];
            vis[i]=false;
        }

        int ans=0;
        int free=0;
        int onecnt=0;
        int poscnt=0;
        for(int p=30;p>=0;p--){
            for(int i=1;i<=n;i++){
                tmp[i]=(val[i]>>p)&1;
            }
            int revcnt=0;
            for(int i=1;i<n;i++){
                if(tmp[i]==1&&tmp[i+1]==0&&!vis[i]){
                    revcnt++;
                }
            }
            // for(int i=1;i<=poscnt;i++){
            //     if(tmp[pos[i]]==1&&tmp[pos[i]+1]==0){
            //         revcnt--;
            //     }
            // }

            if(revcnt==0){
                for(int i=1;i<n;i++){
                    if(tmp[i]==0&&tmp[i+1]==1&&!vis[i]){
                        vis[i]=true;
                    }
                }
            }

            if(revcnt>free){
                onecnt++;
                free+=(1<<onecnt)-1;
                ans+=(1<<p);
            }
            else{
                for(int i=1;i<n;i++){
                    if((tmp[i]==1&&tmp[i+1]==0)&&!vis[i]){
                        free--;
                        vis[i]=true;
                        pos[++poscnt]=i;
                    }
                }
            }

            // cout<<"   "<<ans<<' '<<free<<' '<<onecnt<<endl;
        }
        cout<<ans<<endl;
    }
    return 0;
}