#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
int a[MAXN];
int b[MAXN];
int cnt[MAXN];
// int pos1[MAXN];
// int pos2[MAXN];
vector<int>pos[MAXN];
int st[MAXN];

pair<int,int> ans[MAXN*3];
int cost;
int nodecnt;

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        nodecnt=0,cost=0;
        for(int i=1;i<=n;i++){
            cnt[i]=0;
            pos[i].clear();
            st[i]=0;
        }
        for(int i=1;i<=n;i++){
            cin>>a[i];
            cnt[a[i]]++;
        }
        for(int i=1;i<=n;i++){
            cin>>b[i];
            cnt[b[i]]++;
        }
        for(int i=1;i<=n;i++){
            pos[a[i]].push_back(i);
            pos[b[i]].push_back(i);
        }
        
        bool flag=false;
        for(int i=1;i<=n;i++){
            if(cnt[i]%2){
                flag=true;
                break;
            }
        }
        if(flag){
            cout<<-1<<endl;
            continue;
        }

        for(int i=1;i<=n;i++){
            if(a[i]==b[i]){
                st[a[i]]+=2;
                continue;
            }
            int d1=pos[a[i]][st[a[i]]+1]-i;
            int d2=pos[b[i]][st[b[i]]+1]-i;
            // cout<<i<<":  "<<pos[a[i]][st[a[i]]+1]<<' '<<pos[b[i]][st[b[i]]+1]<<' '<<d1<<' '<<d2<<endl;
            if(d1<=d2){
                if(b[pos[a[i]][st[a[i]]+1]]==a[i]){
                    ans[++nodecnt]={pos[a[i]][st[a[i]]+1],pos[a[i]][st[a[i]]+1]};
                    swap(a[pos[a[i]][st[a[i]]+1]],b[pos[a[i]][st[a[i]]+1]]);
                }
                cost+=d1;
                ans[++nodecnt]={pos[a[i]][st[a[i]]+1],i};
                pos[b[i]][st[b[i]]]=pos[a[i]][st[a[i]]+1];
                a[pos[a[i]][st[a[i]]+1]]=b[i];
                st[a[i]]+=2;
            }
            else{
                if(a[pos[b[i]][st[b[i]]+1]]==b[i]){
                    ans[++nodecnt]={pos[b[i]][st[b[i]]+1],pos[b[i]][st[b[i]]+1]};
                    swap(b[pos[b[i]][st[b[i]]+1]],a[pos[b[i]][st[b[i]]+1]]);
                }
                cost+=d2;
                ans[++nodecnt]={i,pos[b[i]][st[b[i]]+1]};
                // cout<<' '<<nodecnt<<' '<<ans[nodecnt].first<<' '<<ans[nodecnt].second<<endl;
                pos[a[i]][st[a[i]]]=pos[b[i]][st[b[i]]+1];
                b[pos[b[i]][st[b[i]]+1]]=a[i];
                st[b[i]]+=2;
            }
        }

        cout<<cost<<' '<<nodecnt<<endl;
        for(int i=1;i<=nodecnt;i++){
            cout<<ans[i].first<<' '<<ans[i].second<<endl;
        }
    }
    return 0;
}
/*
 3
 3
 1 1 3
 3 2 2
 4
 1 2 2 3
 4 4 3 1
 2
 1 1
 2 1

 1
 10
3 3 1 3 3 3 1 6 3 1
2 6 1 5 5 2 2 4 2 4
 */