#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int help[MAXN];//只需要将x下标离散化
struct node{
    int x,y;
}nums[MAXN];

int tree1[MAXN];//上半部分的下标和x相关的树状数组
int tree2[MAXN];//下半部分的下标和x相关的树状数组

bool cmp(node a,node b){
    return a.y<b.y;
}

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int lowbit(int x){
    return x&(-x);
}

inline int find(int val){
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

void add(int *tree,int x,int val){
    while(x<=m){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

int query(int *tree,int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

bool check(int limit){
    for(int i=1;i<=m;i++){
        tree1[i]=tree2[i]=0;
    }
    for(int i=1;i<=n;i++){
        //这里表示的是一开始所有的都是上半部分
        add(tree1,nums[i].x,1);
    }
    int cnt1=n,cnt2=0;//cnt1表示上面有多少个  cnt2表示下面
    int x1=1,x2=n;//表示枚举上面和下面的x
    for(int i=1,j=1;i<=n;i=j){
        //枚举每一个y  通过牛的y坐标  j表示第一个和当前枚举到的牛y下标不一样的
        while(nums[i].y==nums[j].y){
            //表示将所有符合要求的下标的牛从上面删去
            add(tree1,nums[j].x,-1),add(tree2,nums[j].x,1);
            j++;
            cnt1--,cnt2++;
        }
        //找到第一个x使得左上可以满足要求
        while(x1<=n&&query(tree1,x1)<=limit){
            x1++;
        }
        x1--;//要回退一下
        //找到第一个x使得左下可以满足要求
        while(x2&&query(tree2,x2)>limit){
            x2--;
        }
        //这里要特别注意一下为什么x1 x2的变化不一样 一个从大到小 一个从小到大
        //因为y一直在逐渐上移  上部分一定逐渐减少 左上部分也会减少 所以x从小到大  从而维持左上部分数量的稳定
        //而下部分逐渐增多  如果x还是从小到大 那么可能x还要回退  因为下部分如果增长的特别多 可能x在更小的时候就可以

        int x=min(x1,x2);
        if(cnt1-query(tree1,x)<=limit&&cnt2-query(tree2,x)<=limit)
            return true;
    }
    return false;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].x=read(),nums[i].y=read();
        help[i]=nums[i].x;
    }
    sort(nums+1,nums+n+1,cmp);
    sort(help+1,help+n+1);
    for(int i=1;i<=n;i++){
        if(help[i]!=help[i-1]){
            help[++m]=help[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].x=find(nums[i].x);
    }
    int l=n/4,r=n,ans=n;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}