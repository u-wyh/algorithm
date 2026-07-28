#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m,p;

int doorkey[MAXN];
int keyblock[MAXN];
int belong[MAXN];
int in[MAXN];
int lt[MAXN];
int rt[MAXN];
int que[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m>>p;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        doorkey[x]=y;
    }

    int cnt=1;
    belong[1]=1;
    for(int i=2;i<=n;i++){
        if(doorkey[i-1]!=0){
            cnt++;
        }

        belong[i]=cnt;
    }

    for(int i=1;i<n;i++){
        if(doorkey[i]!=0){
            keyblock[belong[i]]=belong[doorkey[i]];
        }
    }

    for(int i=1;i<cnt;i++){
        if(keyblock[i]<=i){
            in[i]++;
        }
        else{
            in[i+1]++;
        }
    }

    int l=1,r=0;

    for(int i=1;i<=cnt;i++){
        lt[i]=rt[i]=i;
        if(in[i]==0){
            que[++r]=i;
        }
    }

    while(l<=r){
        int x=que[l++];

        while(true){
            bool flag=false;

            if(lt[x]>1&&keyblock[lt[x]-1]>=lt[x]&&keyblock[lt[x]-1]<=rt[x]){
                lt[x]=lt[lt[x]-1];
                flag=true;
            }
            if(rt[x]<cnt&&keyblock[rt[x]]>=lt[x]&&keyblock[rt[x]]<=rt[x]){
                rt[x]=rt[rt[x]+1];
                flag=true;
            }

            if(!flag){
                break;
            }
        }

        if(x>1&&keyblock[x-1]<=x-1){
            if(--in[x-1]==0){
                que[++r]=x-1;
            }
        }
        if(x<cnt&&keyblock[x]>x){
            if(--in[x+1]==0){
                que[++r]=x+1;
            }
        }
    }

    while(p--){
        int s,t;
        cin>>s>>t;
        s=belong[s];
        t=belong[t];
        if(lt[s]<=t&&t<=rt[s]){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}