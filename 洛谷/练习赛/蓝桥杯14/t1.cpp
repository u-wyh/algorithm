#include<bits/stdc++.h>
using namespace std;

inline int fun(int X){
    int ans=0;
    while(X){
        ans++;
        X/=10;
    }
    return ans;
}

inline bool check(int X,int cnt){
    int ans=0;
    for(int i=0;i<cnt/2;i++){
        ans+=(X%10);
        X/=10;
    }
    for(int i=0;i<cnt/2;i++){
        ans-=(X%10);
        X/=10;
    }
    return ans==0;
}

int main()
{
    int ans=0;
    int X=1e8;
    for(int i=11;i<=X;i++){
        int cnt=fun(i);
        // cout<<i<<' '<<cnt<<endl;
        if(cnt%2){
            i*=10;
            continue;
        }
        if(check(i,cnt)){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}