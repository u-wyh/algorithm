#include<bits/stdc++.h>
using namespace std;

int n,m;
int score[21];
string ymd[1005],hms[1005];
int id[1005],val[1005];
bool vis[21];
int ans[1005];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>ymd[i]>>hms[i]>>id[i]>>val[i];
        if(val[i]>score[id[i]]){
            score[id[i]]=val[i];
        }
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(vis[id[i]]){
            continue;
        }
        if(score[id[i]]==val[i]){
            vis[id[i]]=true;
            ans[++cnt]=i;
            // cout<<ymd[i]<<' '<<hms[i]<<' '<<id[i]<<' '<<val[i]<<endl;
        }
    }
    for(int i=1;i<cnt;i++){
        cout<<ymd[ans[i]]<<' '<<hms[ans[i]]<<' '<<id[ans[i]]<<' '<<val[ans[i]]<<endl;
    }
    cout<<ymd[ans[cnt]]<<' '<<hms[ans[cnt]]<<' '<<id[ans[cnt]]<<' '<<val[ans[cnt]];
    return 0;
}