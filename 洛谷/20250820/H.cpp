#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+1;

int n;
int nums[11];
int a[11];
int b[11];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    int ans=0;
    for(int i=0;i<MAXN;i++){
        bool flag=false;
        for(int j=1;j<=n;j++){
            if(i*a[j]>nums[j]){
                flag=true;
                break;
            }
        }
        if(flag){
            break;
        }
        int minval=MAXN;
        for(int j=1;j<=n;j++){
            if(b[j])
                minval=min(minval,(nums[j]-i*a[j])/b[j]);
        }
        ans=max(ans,i+minval);
    }
    cout<<ans<<endl;
    return 0;
}