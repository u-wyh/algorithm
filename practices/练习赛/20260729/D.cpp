#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int arr[MAXN];
int tmp[MAXN];

void compute(int n){
    int pos=n;
    for(int i=1;i<=n;i++){
        if(arr[i]==1){
            pos=i;
            break;
        }
    }
    int p=1;
    for(int i=pos;i<=n;i++,p++){
        tmp[p]=arr[i];
    }
    for(int i=1;i<pos;i++,p++){
        tmp[p]=arr[i];
    }

    for(int i=1;i<n;i++){
        cout<<tmp[i]<<' ';
    }
    cout<<tmp[n]<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        if(n==1){
            cout<<1<<endl;
            continue;
        }
        else if(n==3){
            cout<<"1 3 2"<<endl;
            continue;
        }

        if(n%2==1){
            for(int i=1,v=n/2+1;i<=n-3;i+=2,v++){
                arr[i]=v;
            }
            
            for(int i=2,v=n/2;i<=n-3;i+=2,v--){
                arr[i]=v;
            }

            arr[n]=n-1;
            arr[n-1]=1;
            arr[n-2]=n;
        }
        else{
            for(int i=1,v=n/2+1;i<=n;i+=2,v++){
                arr[i]=v;
            }
            
            for(int i=2,v=n/2;i<=n;i+=2,v--){
                arr[i]=v;
            }
        }
        compute(n);
        // for(int i=1;i<n;i++){
        //     cout<<arr[i]<<' ';
        // }
        // cout<<arr[n]<<endl;
    }
    return 0;
}