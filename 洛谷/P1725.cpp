#include<bits/stdc++.h>
using namespace std;
#define MAX 200005

int n,L,R;
int a[MAX],f[MAX];
int h=0,t=0,ans=-2e9;
int q[MAX];

int main()
{
    cin>>n>>L>>R;
    for(int i=0;i<=n;i++){
        cin>>a[i];
        if(L==R&&i%L==0)
            ans+=a[i];
    }
    if(L==R)
    {
        cout<<ans+2e9<<endl;
        return 0;
    }
    for(int j=L;j<=n;j++){
        int i=j-L;
        while(h<t&&f[q[t]]<=f[i]){
            t--;
        }
        q[t++]=i;
        while(h<t&&i-q[h]>R){
            h++;
        }
        f[i]=a[i]+f[q[h]];
        if(i+R>n)
            ans=max(f[i],ans);
    }
    cout<<ans<<endl;
    return 0;
}
