#include<bits/stdc++.h>
using namespace std;

int compute(int x){
    if(x>100){
        return 100;
    }
    if(x%10==0){
        return x-10;
    }
    else{
        return x-x%10;
    }
}

int main()
{
    int n;
    cin>>n;
    int ans=compute(n);
    printf("Gong xi nin! Nin de ti zhong yue wei: %d duo jin",ans);
    return 0;
}