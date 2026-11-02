#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
int a[MAXN];
int b[MAXN];

priority_queue<int>heap;

bool check(int limit){
    while(!heap.empty()){
        heap.pop();
    }

    int now=0;
    for(int i=1;i<=n;i++){
        now+=a[i];
        heap.push(b[i]);

        while(now<0){
            if(heap.empty()){
                return false;
            }
            if(limit<=0){
                return false;
            }
            limit--;
            int u=heap.top();
            heap.pop();
            now+=u;
        }
    }
    return true;
}

signed main()
{
    // heap.push(1);
    // heap.push(2);
    // cout<<heap.top()<<endl;
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }

    int l=0,r=n,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}