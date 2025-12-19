#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int max11,min11;
int max01,min01;
int max10,min10;
int max00,min00;

struct node{
    int x,y;
};
node nums[MAXN];

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
    return a.x<b.x;
}

int main()
{
    n=read();
    max11=INT_MIN,min11=INT_MAX;
    max10=INT_MIN,min10=INT_MAX;
    max01=INT_MIN,min01=INT_MAX;
    max00=INT_MIN,min00=INT_MAX;
    for(int i=1;i<=n;i++){
        int x,y;
        x=read(),y=read();
        nums[i]={x,y};
        int val1,val2,val3,val4;
        val1=x+y,val2=-x+y,val3=x-y,val4=-x-y;
        max11=max(max11,val1),min11=min(min11,val1);
        max01=max(max01,val2),min01=min(min01,val2);
        max10=max(max10,val3),min10=min(min10,val3);
        max00=max(max00,val4),min00=min(min00,val4);
    }

    sort(nums+1,nums+n+1,cmp);

    int ans=INT_MAX;
    for(int i=1;i<=n;i++){
        int val1,val2,val3,val4;
        val1=nums[i].x+nums[i].y;
        val2=-nums[i].x+nums[i].y;
        val3=nums[i].x-nums[i].y;
        val4=-nums[i].x-nums[i].y;

        int maxdist=max({val1-min11,max11-val1,val2-min01,max01-val2,
                         val3-min10,max10-val3,val4-min00,max00-val4});
        
        int mindist=INT_MAX;
        int st=max(1,i-500);
        int en=min(n,i+500);
        for(int j=st;j<=en;j++){
            if(j==i){
                continue;
            }
            mindist=min(mindist,abs(nums[i].x-nums[j].x)+abs(nums[j].y-nums[i].y));
        }

        ans=min(ans,maxdist-mindist);
    }
    cout<<ans<<endl;
    return 0;
}