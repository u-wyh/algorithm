#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n;
int arr[MAXN],minarr[MAXN],ans[MAXN];
long long sum[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum[i]=sum[i-1]+arr[i];
        //printf("%3d",sum[i]);
    }
    //printf("\n");
    minarr[n]=arr[n];
    for(int i=n-1;i>=1;i--){
        minarr[i]=min(minarr[i+1],arr[i]);
    }
    /*
    for(int i=1;i<=n;i++){
        printf("%3d",minarr[i]);
    }
    printf("\n");
    */
    int sz=1;
    long long K=0;
    for(int i=1;i<=(n-2);i++){
        long long temp=(sum[n]-sum[i]-minarr[i+1]);
        //printf("%lld %lld\n",temp,K);
        if(K*(n-i-1)<=temp){
            if(K*(n-i-1)==temp){
                ans[sz++]=i;
            }else{
                K=temp/(n-i-1);
                sz=1;
                ans[sz++]=i;
            }
        }
    }
    for(int i=1;i<sz;i++)
        cout<<ans[i]<<endl;
    return 0;
}
