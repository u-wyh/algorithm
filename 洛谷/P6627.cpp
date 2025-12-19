//https://www.cnblogs.com/riju-yuezhu/p/13192826.html
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
struct node{
    int op,l,r,val;
}nums[MAXN];
int help[MAXN*4];
int tot=0;
int m=1;
int val[MAXN*4];

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


int find(int val){
    int l=1,r=m,ans=m;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    int n;
    cin>>n;
    help[++tot]=0;//这个也可能是答案
    for(int i=1;i<=n;i++){
        nums[i].op=read();
        if(nums[i].op==1){
            nums[i].l=read(),nums[i].r=read(),nums[i].val=read();
            help[++tot]=nums[i].l;
            help[++tot]=nums[i].l-1;
            help[++tot]=nums[i].r;
            help[++tot]=nums[i].r+1;
        }
        else{
            nums[i].l=read(),nums[i].val=read();
            help[++tot]=nums[i].l;
            help[++tot]=nums[i].l-1;
            help[++tot]=nums[i].l+1;
        }
    }
    //答案只可能来自于help数组  其余数字不可能
    sort(help+1,help+tot+1);
    for(int i=2;i<=tot;i++){
        if(help[i]!=help[i-1]){
            help[++m]=help[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].l=find(nums[i].l);
        if(nums[i].op==1){
            nums[i].r=find(nums[i].r);
            val[nums[i].l]^=nums[i].val;
            val[nums[i].r+1]^=nums[i].val;
        }
        else if(nums[i].op==2){
            val[nums[i].l]^=nums[i].val;
            val[nums[i].l+1]^=nums[i].val;
        }
        else{
            val[1]^=nums[i].val;
            val[nums[i].l]^=nums[i].val;
            val[nums[i].l+1]^=nums[i].val;
        }
    }
    int ans=val[1],sub=1;
    for(int i=2;i<=m;i++){
        val[i]^=val[i-1];
        if(val[i]>ans){
            ans=val[i];
            sub=i;
        }
        else if(val[i]==ans){
            if(abs(help[i])<=abs(help[sub])){
                sub=i;
            }
        }
    }
    cout<<ans<<' '<<help[sub]<<endl;
    return 0;
}
