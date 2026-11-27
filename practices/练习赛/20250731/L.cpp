// 这道题我的策略和题解是一样的  都是按照左端点排序   
// 只不过题解应该是线性的做法  我的是带了log的   但这个数据量也不会超时吧
// 我的具体做法：
// 大思路是用最少的左括号满足所有的要求  剩余的全部放在最左边
// 首先要满足所有的要求  左括号如果需要添加的话  那么一定是添加在一个要求的最左端
// 那么我首先将所有的最左端全部加上一个左括号  如果是没有必要的  就删除
// 判断是否必要   最优解应该是线性的  我使用了树状数组  但对答案应该没有影响啊
// 不知道哪里有问题
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
int tree[MAXN<<1];
struct node{
    int l,r;
}nums[MAXN];
int ok[MAXN<<1];

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
    if(a.l==b.l){
        return a.r>b.r;
    }
    return a.l<b.l;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=2*n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        for(int i=1;i<=2*n;i++){
            tree[i]=0;
            ok[i]=0;
        }
        for(int i=1;i<=m;i++){
            nums[i].l=read(),nums[i].r=read();
            add(nums[i].l,1);
            ok[nums[i].l]++;
        }
        sort(nums+1,nums+m+1,cmp);
        for(int i=m;i>=1;i--){
            if((query(nums[i].r)-query(nums[i].l-1))>=2){
                add(nums[i].l,-1);
                ok[nums[i].l]--;
            }
        }
        int all=0;
        for(int i=1;i<=2*n;i++){
            if(ok[i]){
                all++;
            }
        }
        if(all>n){
            cout<<-1<<endl;
            continue;
        }
        all=n-all;
        int u=1;
        while(all){
            if(ok[u]==0){
                ok[u]=1;
                all--;
            }
            u++;
        }
        int sum=0;
        bool flag=false;
        for(int i=1;i<=2*n;i++){
            if(ok[i]){
                sum++;
            }
            else{
                sum--;
            }
            if(sum<0){
                flag=true;
                break;
            }
        }
        if(flag){
            cout<<-1<<endl;
        }
        else{
            for(int i=1;i<=2*n;i++){
                if(ok[i]){
                    cout<<'(';
                }
                else{
                    cout<<')';
                }
            }
            cout<<endl;
        }
    }
    return 0;
}