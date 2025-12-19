#include<bits/stdc++.h>
using namespace std;

int n;
int arr[20];
int sum[100];
multiset<int>val;
multiset<int>::iterator it;

bool check(int a){
    arr[1]=a;
    for(int i=2;i<=n;i++){
        int v=*val.begin();
        arr[i]=v-arr[1];
        it=val.begin();
        val.erase(it);
        if(arr[i]<arr[i-1]){
            return false;
        }
        for(int j=1;j<=i-2;j++){
            it=val.find(arr[i]+arr[j+1]);
            if(it==val.end()){
                return false;
            }
            else{
                val.erase(it);
            }
        }
    }
    return true;
}

int main()
{
    while(cin>>n){
        bool flag=false;
        for(int i=1;i<=n*(n-1)/2;i++){
            cin>>sum[i];
        }
        sort(sum+1,sum+n*(n-1)/2+1);
        for(int i=0;i<=sum[1]/2;i++){
            val.clear();
            for(int j=1;j<=n*(n-1)/2;j++){
                val.insert(sum[j]);
            }
            if(check(i)){
                for(int j=1;j<=n;j++){
                    cout<<arr[j]<<' ';
                }
                cout<<endl;
                flag=true;
                break;
            }
        }
        if(!flag){
            cout<<"Impossible"<<endl;
        }
    }
    return 0;
}