#include<bits/stdc++.h>
using namespace std;
const int MAXN = 35;
const int MAXM = 105;

int n;
int val[MAXN];
int ord[MAXN];
int pos[MAXM];
bool flag=true;

void dfs(int l,int r,int lt,int rt,int d){
    if(lt>rt){
        return ;
    }
    int root=r;
    if(val[root]%d){
        flag=false;
    }
    if(flag){
        int len=0;
        for(len;;len++){
            if(ord[lt+len]==root){
                break;
            }
        }
        len--;
        dfs(l,l+len,lt,lt+len,d+1);
        dfs(l+len+1,r-1,lt+len+2,rt,d+1);
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        flag=true;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>val[i];
            pos[val[i]]=i;
        }
        for(int i=1;i<=n;i++){
            int val;
            cin>>val;
            ord[i]=pos[val];
        }
        dfs(1,n,1,n,1);
        if(flag){
            cout<<1<<endl;
        }
        else{
            cout<<0<<endl;
        }
    }
    return 0;
}