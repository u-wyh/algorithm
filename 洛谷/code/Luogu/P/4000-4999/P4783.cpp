#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 405;

int n;
int nums[MAXN][MAXN<<1];

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

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

void gauss(){
    for(int i=1;i<=n;i++){
        int t=i;
        for(int j=i+1;j<=n;j++){
            if(nums[j][i]>nums[t][i]){
                t=j;
            }
        }
        if(t!=i){
            swap(nums[t],nums[i]);
        }
        if(!nums[i][i]){
            cout<<"No Solution"<<endl;
            return ;
        }

        int inv=power(nums[i][i],MOD-2);
        for(int j=1;j<=n;j++){
            if(j==i){
                continue;
            }
            int p=nums[j][i]*inv%MOD;
            for(int k=i;k<=2*n;k++){
                nums[j][k]=((nums[j][k]-p*nums[i][k])%MOD+MOD)%MOD;
            }
        }
    }

    for(int i=1;i<=n;i++){
        int inv=power(nums[i][i],MOD-2);
        for(int j=n+1;j<=2*n;j++){
            nums[i][j]=(nums[i][j]*inv%MOD+MOD)%MOD;
            cout<<nums[i][j]<<' ';
        }
        cout<<endl;
    }
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            nums[i][j]=read();
        }
        nums[i][i+n]=1;
    }
    gauss();
    return 0;
}