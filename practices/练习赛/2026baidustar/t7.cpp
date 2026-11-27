#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n;
int all=0;
int val[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n;
    int maxv=-1;
    int cnt=0;
    bool flag=false;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        if(val[i]>=0){
            all+=val[i];
        }
        else{
            cnt++;
        }
        if(val[i]>maxv){
            maxv=val[i];
            flag=true;
        }
        else if(val[i]==maxv){
            flag=false;
        }
    }
    int rest=n-all;
    
    for(int i=1;i<=n;i++){
        if(val[i]!=-1){
            if(flag&&maxv==val[i]){
                int d=0;
                if(cnt)
                    d=(rest+cnt-1)/cnt;
                if(val[i]>d){
                    cout<<i<<' ';
                }
            }
        }
        else{
            if(rest>maxv){
                cout<<i<<' ';
            }
        }
    }
    return 0;
}