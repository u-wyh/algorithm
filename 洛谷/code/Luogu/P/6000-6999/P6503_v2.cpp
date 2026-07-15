#include<bits/stdc++.h>
using namespace std;

typedef long long ll;  // 使用 ll 作为 long long 的别名
const ll MN = 3e5 + 5;

ll nums[MN];
ll Lmax[MN], Rmax[MN], Lmin[MN], Rmin[MN];
ll n,ans=0;
ll st[MN];
int cur;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>nums[i];
    int r=0;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]<nums[i]){
            cur=st[--r];
            Rmax[cur]=i;
            Lmax[cur]=r<=0?0:st[r-1];
        }
        st[r++]=i;
    }
    while(r>0){
        cur=st[--r];
        Rmax[cur]=n+1;
        Lmax[cur]=r>0?st[r-1]:0;
    }

    r=0;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]>nums[i]){
            cur=st[--r];
            Rmin[cur]=i;
            Lmin[cur]=r<=0?0:st[r-1];
        }
        st[r++]=i;
    }
    while(r>0){
        cur=st[--r];
        Rmin[cur]=n+1;
        Lmin[cur]=r>0?st[r-1]:0;
    }

    /*
    for(int i=1;i<=n;i++)
        printf("%3d",Rmax[i]);
    printf("\n");
    for(int i=1;i<=n;i++)
        printf("%3d",Lmax[i]);
    printf("\n");
    for(int i=1;i<=n;i++)
        printf("%3d",Rmin[i]);
    printf("\n");
    for(int i=1;i<=n;i++)
        printf("%3d",Lmin[i]);
    printf("\n");
    */

    for(int i=1;i<=n;i++){
        ans+=nums[i]*(i-Lmax[i])*(Rmax[i]-i);
        ans-=nums[i]*(i-Lmin[i])*(Rmin[i]-i);
    }
    cout<<ans<<endl;

    return 0;
}
