#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005;
const int MAXM = 2e6+4000;

struct node{
    int x,y,c,k;
}nums[MAXN];
struct edge{
    int st,en,val;
}arr[MAXM];
int cnt=0;
int fa[MAXN];
int n,sum;
vector<int>ans;
vector<pair<int,int>>res;

bool cmp(edge a,edge b){
    return a.val<b.val;
}

int find(int i){
    return fa[i]==i?i:fa[i]=find(fa[i]);
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i].c;
        arr[++cnt].st=0;//超级源点建边
        arr[cnt].en=i;
        arr[cnt].val=nums[i].c;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i].k;
        for(int j=i-1;j>=1;j--){
            arr[++cnt].st=j;
            arr[cnt].en=i;
            arr[cnt].val=(abs(nums[i].x-nums[j].x)+abs(nums[i].y-nums[j].y))*(nums[i].k+nums[j].k);
        }
    }
    sort(arr+1,arr+cnt+1,cmp);
    for(int i=1;i<=cnt;i++){
        int x=find(arr[i].st);
        int y=find(arr[i].en);
        if(x==y){
            continue;
        }
        if(arr[i].st==0){
            ans.push_back(arr[i].en);
        }
        else{
            res.push_back({arr[i].st,arr[i].en});
        }
        fa[x]=y;
        sum+=arr[i].val;
    }
    cout << sum << endl << ans.size() << endl;
	for(auto i:ans)
        cout <<i << ' ';
	cout << endl;
	cout << res.size() << endl;
	for(auto t:res){
		cout <<t.first <<" "<<t.second <<endl;
	}
    return 0;
}
