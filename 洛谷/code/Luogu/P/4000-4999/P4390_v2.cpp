#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 2e6+5;

int n,m,q;
struct node{
    int x,y,d,q;
};
node arr[MAXN];
int ans[MAXN];

int tree[MAXM];

void addpeople(int x,int y,int v){
    ++m;
    arr[m]={x,y,v,0};
}

void addquery(int x,int y,int d,int q){
    ++m;
    arr[m]={x,y,d,q};
}

int lowbit(int x){
    return x&-x;
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

bool cmp(node a,node b){
    return a.x<b.x;
}

void merge(int l,int mid,int r){
    int p1,p2;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&arr[p1+1].x<=arr[p2].x){
            p1++;
            if(arr[p1].q==0){
                add(arr[p1].y,arr[p1].d);
            }
        }
        if(arr[p2].q){
            ans[arr[p2].q]+=arr[p2].d*query(arr[p2].y);
        }
    }

    for(int i=l;i<=p1;i++){
        if(arr[i].q==0){
            add(arr[i].y,-arr[i].d);
        }
    }

    sort(arr+l,arr+r+1,cmp);
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int op;
    cin>>op>>n;
    n++;

    cin>>op;
    while(op!=3){
        if(op==1){
            int x,y,c;
            cin>>x>>y>>c;
            x++,y++;
            addpeople(x,y,c);
        }
        else if(op==2){
            ++q;
            int x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            x1++,y1++,x2++,y2++;
            addquery(x2,y2,1,q);
            addquery(x1-1,y1-1,1,q);
            addquery(x2,y1-1,-1,q);
            addquery(x1-1,y2,-1,q);
        }
        cin>>op;
    }

    cdq(1,m);

    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}