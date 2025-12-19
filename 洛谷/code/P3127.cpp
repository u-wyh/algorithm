#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

struct node{
    int v,pos;
}nums[MAXN];
int n;
int ans;
bool ok[MAXN];

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

bool cmp(node a,node b){
    return a.pos<b.pos;
}

bool compute(int x){
    int s=nums[x+1].pos-nums[x].pos;
    int l=x,r=x+1;
    while(l>=1&&r<=n){
        bool flag=false;
        if(s>nums[l].v){
            flag=true;
            l--;
            if(ok[l]){
                ok[x]=true;
                return true;
            }
            s+=(nums[l+1].pos-nums[l].pos);
        }
        if(s>nums[r].v){
            flag=true;
            r++;
            if(ok[r-1]){
                ok[x]=true;
                return true;
            }
            s+=(nums[r].pos-nums[r-1].pos);
        }
        if(!flag){
            return false;
        }
    }
    return true;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].v=read(),nums[i].pos=read();
    }
    sort(nums+1,nums+n+1,cmp);
    ok[0]=true,ok[n]=true;
    for(int i=1;i<n;i++){
        if(!compute(i)){
            ans+=nums[i+1].pos-nums[i].pos;
        }
    }
    cout<<ans<<endl;
    return 0;
}
