#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    int ans=0;
    while(cin>>n&&(n==1||n==0)){
        if(n){
            ans++;
        }
        else{
            cout<<ans<<endl;
        }
    }
    return 0;
}