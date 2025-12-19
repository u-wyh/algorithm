#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 100005;

int n,m;
int arr[MAXN],tree1[MAXN],tree2[MAXN];

int lowbit(int x){
    return x & -x;
}

void add(int *tree,int i,int  v){
    //printf("%3lld %3lld \n",i,v);
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //每一次都加上自己最右侧的1
    }
}

int sum(int *tree,int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
    }
    return ans;
}

int query(int i){
    return sum(tree1,i)*i-sum(tree2,i);
}

void update(int i,int v){
    //printf("%4lld %4lld %4lld \n",i,v,arr[i]);
    add(tree1,i,v-arr[i]);
    add(tree2,i,(i-1)*(v-arr[i]));
    arr[i]=v;
}

signed main()
{
    cin>>n>>m;
    int a;
    for(int i=1;i<=n;i++){
        cin>>a;
        update(i,a);
        //printf("%3lld",tree1[i]);
    }
    /*
    cout<<endl;
    for(int i=1;i<=n;i++)
        printf("%3lld",arr[i]);
    cout<<endl;
    */
    string op;
    for(int i=1,k,v;i<=m;i++){
        cin>>op;
        if(op=="Modify"){
            cin>>k>>v;
            update(k,v);
        }else{
            cin>>k;
            cout<<query(k)<<endl;
        }
    }
    return 0;
}
