#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n,t;
int all1,all2;
int d1[MAXN];
int d2[MAXN];
int d[MAXN];
int pos[MAXN];
map<int,int>mp1;
map<int,int>mp2;

int main()
{
    cin>>n>>t;
    if(n==1){
        printf("? 1\n");
        fflush(stdout);
        int d;
        scanf("%d",&d);
        printf("! %d\n",(1+d));
    }
    else{
        printf("? 1\n");
        fflush(stdout);
        for(int i=1;i<=n;i++){
            scanf("%d",&d1[i]);
            all1+=d1[i];
        }
        printf("? 1000000000");
        fflush(stdout);
        for(int i=1;i<=n;i++){
            scanf("%d",&d2[i]);
            all2+=d2[i];
        }
        int reald=all1+all2-1000000000+1;
        pos[1]=all1-reald+1;
        pos[n]=1000000000-(all2-reald);
        if(n==2){
            printf("! %d %d\n",pos[1],pos[2]);
            return 0;
        }
        for(int i=1;i<=n;i++){
            mp1[d1[i]]++;
        }
        mp1[pos[1]-1]--;
        for(int i=2;i<n;i++){
            printf("? %d\n",pos[i-1]+1);
            fflush(stdout);

            for(int p=1;p<=n;p++){
                scanf("%d",&d[p]);
            }
            if(d[1]==0){
                pos[i]=pos[i-1]+1;
                continue;
            }
            for(int p=1;p<=n;p++){
                mp2[d[p]]++;
            }
            int dis=0;
            for(int p=1;p<=n;p++){
                if(d[p]==d[p-1]){
                    continue;
                }
                if(mp2[d[p]]==mp1[d[p]]+1&&d[p]!=1){
                    dis=d[p];
                    break;
                }
                else if(mp2[d[p]]==mp1[d[p]]+2){
                    dis=d[p];
                    break;
                }
            }
            pos[i]=pos[i-1]+1+dis;
            for(int p=1;p<=n;p++){
                mp2[d[p]]=0;
            }

        }
        printf("! ");
        for(int i=1;i<=n;i++){
            printf("%d ",pos[i]);
        }
    }
    return 0;
}