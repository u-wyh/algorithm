#include<bits/stdc++.h>
using namespace std;

int ans=0;

void compute(int x){
    while(x){
        int k=x%10;
        if(k==2){
            ans++;
        }
        x/=10;
    }
}

int main()
{
    for(int i=1;i<=2020;i++){
        compute(i);
    }
    cout<<ans<<endl;
    return 0;
}