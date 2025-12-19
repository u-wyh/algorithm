#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int ans[MAXN];

int main()
{
    cin>>n;
    if(n%2==1){
        for(int i=1;i<=n;i++){
            cout<<i<<' ';
        }
        return 0;
    }
    else{
        for(int i=1;i<=n;i++){
            if(i%2){
                ans[i]=i+1;
            }
            else{
                ans[i]=i-1;
            }
            cout<<ans[i]<<' ';
        }
    }
    return 0;
}