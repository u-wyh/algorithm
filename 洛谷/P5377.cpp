#include<bits/stdc++.h>
using namespace std;

int f1[100],f2[100],f3[100],f4[100];

int main()
{
    for(int i=4;i<=65;i++){
        f4[i]=i-3;
    }
    f3[3]=1;
    for(int i=4;i<=65;i++){
        f3[i]=f3[i-1]+f4[i];
    }
    f2[2]=1;
    for(int i=3;i<=65;i++){
        f2[i]=f2[i-1]+f3[i];
    }
    f1[0]=1;
    f1[1]=1;
    for(int i=2;i<=65;i++){
        f1[i]=f1[i-1]+f2[i];
    }
    int n;
    while(cin>>n){
        cout<<f1[n]<<endl;
    }
    return 0;
}