#include<bits/stdc++.h>
using namespace std;

int n;
int nums[100005],st[100005],R[100005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>nums[i];
    int cur,r=0;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]<nums[i]){
            cur=st[--r];
            R[cur]=i;
        }
        st[r++]=i;
    }

    while (r > 0) {
        cur = st[--r];
        R[cur] = 0;
    }

    for(int i=1;i<=n;i++)
        cout<<R[i]<<endl;
    return 0;
}
