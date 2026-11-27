#include<bits/stdc++.h>
using namespace std;

int arr[24];

int main()
{
    for(int i=0;i<=23;i++){
        cin>>arr[i];
    }
    int n;
    while(cin>>n){
        if(n<0||n>23){
            break;
        }
        cout<<arr[n]<<' ';
        if(arr[n]>50){
            cout<<"Yes\n";
        }
        else{
            cout<<"No\n";
        }
    }
    return 0;
}