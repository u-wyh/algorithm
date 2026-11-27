#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n;
int tree[MAXN];
int arr[MAXN];

int lowbit(int x){
    return x&-x;
}

void add(int x){
    while(x<=n){
        tree[x]+=1;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        add(arr[i]);
        ans+=i-query(arr[i]);
    }
    // cout<<ans<<endl;
    for(int i=1;i<=n;i++){

        for(int j=1;j<=n;j++){
            tree[j]=0;
        }

        int k=0;
        for(int j=i;j<=n;j++){
            if(i==j&&i==n){
                cout<<ans;
                return 0;
            }

            int tmp=(j-i+1)*(j-i)/2;
            add(arr[j]);
            k+=(j-i)-query(arr[j]-1);
            // cout<<i<<' '<<j<<' '<<tmp<<' '<<k<<endl;
            cout<<(ans-2*k+tmp)<<' ';
        }
    }
    return 0;
}