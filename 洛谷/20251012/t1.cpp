#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int BASE = 131;
const int MOD = 1e9+7;

int n;

string s[MAXN];

struct node{
    int val,val1,val2;
    int len;
};
node nums[MAXN];
// bool ok[MAXN];
map<int,int>mp;

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
    return a.len<b.len;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        nums[i].len=s[i].length();

        int val=0;
        for(int j=0;j<nums[i].len;j++){
            val=(val*BASE+(s[i][j]-'a'+1))%MOD;
        }
        nums[i].val=val;

        val=0;
        for(int j=0;j<nums[i].len-1;j++){
            val=(val*BASE+(s[i][j]-'a'+1))%MOD;
        }
        nums[i].val1=val;
        
        val=0;
        for(int j=1;j<nums[i].len;j++){
            val=(val*BASE+(s[i][j]-'a'+1))%MOD;
        }
        nums[i].val2=val;
    }
    sort(nums+1,nums+n+1,cmp);

    int ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i].len==1){
            // ok[i]=true;
            mp[nums[i].val]=i;
            ans=max(ans,nums[i].len);
        }
        else{
            int id1=mp[nums[i].val1];
            int id2=mp[nums[i].val2];
            if(id1&&id2&&(nums[id1].len==(nums[i].len-1))&&(nums[id2].len==(nums[i].len-1))){
                // ok[i]=true;
                mp[nums[i].val]=i;
                ans=max(ans,nums[i].len);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}