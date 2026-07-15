#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n,m;
int cnt;
int help[MAXN];
struct node{
    int year,val;
}nums[MAXN];
int tree1[MAXN<<2];
int tree[MAXN<<2];

bool cmp(node a,node b){
    return a.year<b.year;
}

int getrank(int val){
    int l=1,r=cnt,ans;
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

void up(int i){
    tree[i]=max(tree[i<<1],tree[i<<1|1]);
    tree1[i]=min(tree1[i<<1],tree1[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=nums[l].val;
        tree1[i]=nums[l].val;
        return ;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

int querymax(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int ans=-2;
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans=max(ans,querymax(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,querymax(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

int querymin(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree1[i];
    }
    else{
        int ans=INT_MAX;
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans=min(ans,querymin(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,querymin(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

int main()
{
    cin>>n;
    int pre;
    cin>>nums[1].year>>nums[1].val;
    pre=nums[1].year-1;
    help[++cnt]=pre;
    nums[n+1].year=pre;
    nums[n+1].val=-1;
    help[++cnt]=nums[1].year;
    pre=nums[1].year;
    for(int i=2;i<=n;i++){
        cin>>nums[i].year>>nums[i].val;
        help[++cnt]=nums[i].year;
        if(nums[i].year-pre>1){
            //cout<<666<<endl;
            help[++cnt]=nums[i].year-1;
            nums[n+cnt-i].year=nums[i].year-1;
            nums[n+cnt-i].val=-1;
        }
        pre=nums[i].year;
    }
    n=cnt;
    sort(help+1,help+n+1);
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        //cout<<nums[i].year<<' '<<nums[i].val<<' ';
        nums[i].year=getrank(nums[i].year);
        //cout<<nums[i].year<<' '<<nums[i].val<<endl;
    }
    //cout<<endl;
    build(1,n,1);
    cin>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        u=getrank(u);
        v=getrank(v);
        //cout<<u<<' '<<v<<endl;
        if(nums[u].val!=-1&&nums[v].val!=-1){
            if(nums[u].val<nums[v].val){
                cout<<"false"<<endl;
                continue;
            }
            if(u+1==v){
                cout<<"true"<<endl;
                continue;
            }
            if(querymax(u+1,v-1,1,n,1)>=nums[v].val){
                cout<<"false"<<endl;
                continue;
            }
            if(querymin(u+1,v-1,1,n,1)==-1){
                cout<<"maybe"<<endl;
                continue;
            }
            cout<<"true"<<endl;
        }
        else{
            if(nums[u].val==-1&&nums[v].val==-1){
                cout<<"maybe"<<endl;
                continue;
            }
            if(nums[u].val==-1){
                if(u+1==v){
                    cout<<"maybe"<<endl;
                    continue;
                }
                if(querymax(u+1,v-1,1,n,1)>=nums[v].val){
                    cout<<"false"<<endl;
                    continue;
                }
                cout<<"maybe"<<endl;
            }
            else{
                if(u+1==v){
                    cout<<"maybe"<<endl;
                    continue;
                }
                if(querymax(u+1,v-1,1,n,1)>=nums[u].val){
                    cout<<"false"<<endl;
                    continue;
                }
                cout<<"maybe"<<endl;
            }
        }
    }
    return 0;
}
