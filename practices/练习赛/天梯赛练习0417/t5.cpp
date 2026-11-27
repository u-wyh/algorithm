#include<bits/stdc++.h>
using namespace std;

int a[7];
int n;
bool vis[7];

int main()
{
    for(int i=1;i<=6;i++){
        cin>>a[i];
    }
    cin>>n;
    for(int i=1;i<=6;i++){
        if(a[i]>(6-n)){
            cout<<(6-n);
        }
        else{
            cout<<(7-n);
        }
        if(i!=6){
            cout<<' ';
        }
    }
    return 0;
}