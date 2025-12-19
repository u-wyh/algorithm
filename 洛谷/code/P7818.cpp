//P7818
// 前置知识：树状数组  
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n;
long long k;

int arr[MAXN];//一开始的输入数组
int pos[MAXN];//表示每个数字的位置  eg: arr[5]=6  那么pos[6]=5  :5位置上的数字是6  那么6这个数字在5位置上   这个数组是为了vis数组设置的
bool vis[MAXN];//表示i位置的数字是否已经被利用了（即已经填到ans数组中了）
int pre[MAXN];//表示i位置上的数字  在前面有多少个数字比他大

int tree[MAXN];//树状数组
int ans[MAXN];//最终所有数字填好后的数组

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

// 树状数组
inline int lowbit(int x){
	return x&(-x);
}

void add(int x){
	while(x<=n){
		tree[x]+=1;
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

// 小根堆
struct compare{
	bool operator()(const pair<int,int>&a,const pair<int,int>&b){
		if (a.second != b.second) {
            return a.second > b.second; 
        } else {
            return a.first > b.first; 
        }
	}
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;

int main()
{
	scanf("%d %lld",&n,&k);
	for(int i=1;i<=n;i++){
		arr[i]=read();
		pos[arr[i]]=i;
		add(arr[i]);
		pre[arr[i]]=i-query(arr[i]);
	}

	int now=1;//表示该填ans数组的哪一位了
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(k==0){
			//表示没有交换的机会了 直接跳出
			break;
		}

		if(!heap.empty()&&heap.top().second-cnt<=k){
			ans[now++]=heap.top().first;
			vis[pos[heap.top().first]]=1;
			k-=(heap.top().second-cnt);
			heap.pop();
			heap.push({i,pre[i]+cnt});
			cnt++;
		}

		if(k>=pre[i]){
			ans[now++]=i;
			k-=pre[i];
			vis[pos[i]]=1;
			cnt++;
		}
		else{
			heap.push({i,pre[i]+cnt});
		}
	}

	if(k==0){
		//如果k是0  说明肯定还有位置没有填好并且也交换不了了  那么将没有填的数字按照他们的相对顺序填入即可
		//这就是为什么我设置了vis  和  pos数组
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				ans[now++]=arr[i];
			}
		}
	}
	if(k&1){
		//如果k是一个奇数 那么首先可以说明所有数字都有序之后  k还有剩余  因为k!=0
		//那么题目要求必须要交换k次 而且要求要求字典序最小 那么每交换两次 实际上是没有交换的
		//所以等效于交换一次  那么最好的一定是将最后两个数字交换一下
		swap(ans[n-1],ans[n]);
	}
	//输出答案
	for(int i=1;i<=n;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}