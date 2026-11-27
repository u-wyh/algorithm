#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int dep[MAXN];
int nums[MAXN];

int main()
{
    dep[1]=1;
    for(int i=2;i<=200000;i++){
        dep[i]=dep[i/2]+1;
    }
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>nums[i];
        }
        bool flag=false;
        for(int i=2;i<=n;i++){
            if(dep[nums[i]]<dep[nums[i-1]]){
                flag=true;
                break;
            }
        }
        if(flag){
            cout<<"NO"<<endl;
        }
        else{
            cout<<"YES"<<endl;
        }
    }
    return 0;
}