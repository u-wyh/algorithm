// https://www.luogu.com.cn/problem/P1986
// 题意：从排成一列的 n 人中选一些人发麦克风。给定 m 条区间要求，每条规定 [a_i,b_i] 内至少要有 c_i 人拿到麦克风。求最少要发多少支。
// 数据范围：1 ≤ n ≤ 30000，1 ≤ m ≤ 5000，1 ≤ a_i < b_i ≤ n，1 ≤ c_i ≤ b_i−a_i+1。

#include<bits/stdc++.h>
using namespace std;

struct node{
    int l,r,need;
}stu[5005];
bool sound[30005];
int n,m,ans=0;

bool cmp(node a,node b){
    return a.r<b.r;
}


int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>stu[i].l>>stu[i].r>>stu[i].need;
    }
    sort(stu+1,stu+m+1,cmp);
    for(int i=1;i<=m;i++)
	{
		int a=0;//计数
		//先扫一遍统计该声部现有话筒个数
		for(int j=stu[i].l;j<=stu[i].r;j++){
			if(sound[j]){
			    a++;
			}
		}
		//从尾巴开始放
		for(int j=stu[i].r;j>=stu[i].l;j--){
			//够了就退出
			if(a>=stu[i].need){
				break;
			}
			//这里没有话筒就放一个
			if(!sound[j]){
				a++;
				ans++;
				sound[j]=1;
			}
		}
	}
	cout<<ans;
    return 0;
}
