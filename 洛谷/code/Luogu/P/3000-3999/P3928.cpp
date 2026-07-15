#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 3e5+5;

int n,len;
int val[4][MAXN];
int sorted[MAXM];

// 0 目前选的最后一个小于等于x的最大值
// 1 目前选的最后一个大于等于x的最大值  这里需要反向编号
// 2 
int tree[4][MAXM];

int find(int val){
    int l=1,r=len,ans=len;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int lowbit(int x){
    return x&-x;
}

int query(int x,int op){
    int ans=0;
    while(x){
        ans=max(ans,tree[op][x]);
        x-=lowbit(x);
    }
    return ans;
}

void update(int x,int val,int op){
    while(x<=len){
        tree[op][x]=max(tree[op][x],val);
        x+=lowbit(x);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=3;i++){
        for(int j=1;j<=n;j++){
            cin>>val[i][j];
            sorted[++len]=val[i][j];
        }
    }
    sort(sorted+1,sorted+len+1);

    len=1;
    for(int i=2;i<=3*n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }

    for(int i=1;i<=3;i++){
        for(int j=1;j<=n;j++){
            val[i][j]=find(val[i][j]);
        }
    }

    int ans=1;

    for(int i=1;i<=n;i++){
        int id1=val[1][i];
        int id2=val[2][i];
        int id3=val[3][i];

        int rev1=len-id1+1;
        int rev2=len-id2+1;
        int rev3=len-id3+1;

        int dp0=query(id1,0)+1;
        int dp1=query(rev2,1)+1;
        int dp2=query(id3,2)+1;
        int dp3=query(rev3,3)+1;

        ans=max(ans,max(max(dp0,dp1),max(dp2,dp3)));

        update(id1,dp0,0);
        update(rev1,dp0,1);
        update(id1,dp0,2);
        update(rev1,dp0,3);
        
        update(id2,dp1,0);
        update(rev2,dp1,1);
        update(id2,dp1,2);
        update(rev2,dp1,3);
        
        update(id3,dp2,0);
        update(rev3,dp2,1);
        update(id3,dp2,2);
        
        update(id3,dp3,0);
        update(rev3,dp3,1);
        update(rev3,dp3,3);
    }

    cout<<ans<<endl;

    return 0;
}