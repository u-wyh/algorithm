#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n;
int nums[MAXN];
int arr[MAXN];
int help[MAXN];

int mergesort(int l,int r){
    int mid=(l+r)/2;
    if(l==r)
        return 0;
    for(int i=l;i<=r;i++){
        help[i]=arr[i];
    }
    int i=l;
    int j=mid+1;
    int cnt=0;
    for(int k=l;k<=r;k++){
        if(i==mid+1){
            arr[k]=help[j];
            j++;
        }else if(j==r+1){
            arr[k]=help[i];
            i++;
        }else if(help[i]<=help[j]){
            arr[k]=help[i];
            i++;
        }else if(help[j]<help[i]){
            arr[k]=help[j];
            j++;
            cnt+=(mid-i+1);
        }else
            break;
    }
    return cnt;
}

int merge(int l,int r){
    if(l==r)
        return 0;
    int mid=(l+r)/2;
    int ans=0;
    ans+=merge(l,mid);
    ans+=merge(mid+1,r);
    ans+=mergesort(l,r);
    return ans;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=0;i<n;i++){
        for(int j=1;j<=n;j++){
            if(nums[j]>i)
                arr[j]=i;
            else
                arr[j]=nums[j];
        }
        cout<<merge(1,n)<<endl;
    }
    return 0;
}
