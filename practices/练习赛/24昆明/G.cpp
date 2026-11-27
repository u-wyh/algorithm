#include<bits/stdc++.h>
using namespace std;
#define int long long

int gcd(int a,int b){
    if(a<b){
        swap(a,b);
    }
    return b==0?a:gcd(b,a%b);
}

bool dfs(int a,int b,int now){
    // cout<<a<<' '<<b<<' '<<now<<endl;
    if(now==0){
        return a==0&&b==0;
    }
    bool flag=false;
    if(a){
        flag=dfs(a-gcd(a,b),b,now-1);
    }
    if(flag){
        return true;
    }
    if(b){
        flag=dfs(a,b-gcd(a,b),now-1);
    }
    return flag;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int a,b;
        int tmp;
        cin>>a>>b;
        tmp=a;
        int countone=0;
        while(tmp){
            countone++;
            tmp>>=1;
        }
        // cout<<' '<<countone<<endl;
        for(int i=2;i<=2*countone+1;i++){
            // cout<<i<<endl;
            if(dfs(a,b,i)){
                cout<<i<<endl;
                break;
            }
        }
    }
    return 0;
}