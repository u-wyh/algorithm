#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int nxt[MAXN];
int color[MAXN];
int sucdfn[MAXN];
int dfn[MAXN];
int minc[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nxt[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=i,cnt=0;;cnt++,j=nxt[j]){
            if(!color[j]){
                color[j]=i;
                dfn[j]=cnt;
            }
            else if(color[j]==i){
                minc[i]=cnt-dfn[j];
                sucdfn[i]=dfn[j];
                cout<<cnt<<endl;
                break;
            }
            else{
                minc[i]=minc[color[j]];
                sucdfn[i]=cnt+max(0,sucdfn[color[j]]-dfn[j]);
                cout<<minc[i]+sucdfn[i] <<endl;
                break;
            }
        }
    }
    return 0;
}
