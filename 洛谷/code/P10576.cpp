#include<bits/stdc++.h>
using namespace std;

__int128 c=20240601000;

void print(__int128 x){
    if(x==0) {
        cout<<0<<"\n";
        return;
    }
    string res="";
    while(x){
        res=char(x%10+'0')+res;
        x/=10;
    }
    cout<<res<<"\n";
}

int main()
{
    __int128 ans=0;
    for(__int128 i=1;i*i<=c;i++){
        if(c%i==0){
            __int128 a=i,b=c/i;
            __int128 x=(a+b)/2,y=(b-a)/2;
            if(x*x-y*y!=c){
                continue;
            }
            ans+=x*x-c/2;
        }
    }
    print(ans);
    return 0;
}