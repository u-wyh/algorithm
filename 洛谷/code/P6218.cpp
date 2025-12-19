#include<bits/stdc++.h>
using namespace std;

//int cnt[31];//表示还有i位没有填，这i位0比1多或相等的数目
int sum[31];//表示还有i位没有填，这i位0比1多的数目
int a,b;

int C(int n,int m){
    int ans=1;
    for(int i=1;i<=m;i++){
        ans*=(n-i+1);
        ans/=i;
    }
    return ans;
}

int f(int num,int i,int gap,int free){
    //表示数字是num 目前是第i位  0-1数量是gap  free表示前缀是否一样及是否可以自由选择
    if(i==-1){
        if(gap>=0)
            return 1;
        else
            return 0;
    }
    if(free&&(gap==-1)){
        return sum[i];
    }
    int ans=0;
    if(free==0){
        int cur=(num&(1<<i));
        if(cur==1){
            ans+=f(num,i-1,gap+1,1);//表示这个位置填0
            ans+=f(num,i-1,gap-1,0);//表示这个位置填1
        }
        else{
            ans+=f(num,i-1,gap+1,0);
        }
    }
    else{
        //可以随便填，但是还没有直接触发上面的那个 说明差值不是1
            ans+=f(num,i-1,gap+1,1);//表示这个位置填0
            ans+=f(num,i-1,gap-1,1);//表示这个位置填1
    }
    return ans;
}

int cnt(int num){
    int tmp=num;
    int len=0;
    while(tmp){
        len++;
        tmp>>=1;
    }
    //cout<<len<<' ';
    int ans=0;
    for(int i=0;i<len-1;i++){
        ans+=sum[i];//首先将位数不足的情况加上
    }
    cout<<ans<<endl;
    ans+=f(num,len-1,0,0);
    //为什么有free  是因为如果是1000000000  即使第3位0就比1多  但是不能随便选
    return ans;
}

int main()
{
    sum[0]=0;
    for(int i=1;i<=30;i++){
        if(i%2==0){
            int k=C(i,i/2);
            sum[i]=(pow(2,i)-k)/2;
        }
        else{
            sum[i]=pow(2,i-1);
        }
        //cout<<i<<' '<<sum[i]<<endl;
    }
    cin>>a>>b;
    int ans=cnt(b)-cnt(a-1);
    cout<<ans<<endl;
    return 0;
}

//dfs(数的最后若干位,各种限制条件,当前第几位)
//	if 最后一位
//    	return 各种限制条件下的返回值
//    局部变量 ct=当前位的数字
//    局部变量 sum=0;
//    for i=0 to ct-1
//    	sum+=当前位取i时一定无无限制的合法状态数
//        sum+=当前位取i时满足当前限制的合法状态数
//    根据ct更新限制条件 不再满足则return sum
//    return sum+dfs(当前位后的若干位,更新后的限制条件,下一位)
//
//slv(当前数)
//	if(只有一位) return 对应的贡献
//    局部变量 ct;
//    for ct=可能最高位 to 1
//    	if 当前位有数字 break
//    局部变量 nw=当前位数字
//    局部变量 sum=0
//    for i=1 to nw-1
//    	sum+=当前位取i后合法情况任意取的贡献
//    for i=1 to ct-1
//    	for j=1 to 9
//        	sum+=第i位取j后合法情况任意取的贡献
//    sum+=dfs(去掉第一位后的若干位,限制条件,第二位)
//    return sum
//
//main
//	预处理当前位取i的各种条件各种限制的贡献
//    读入 L R
//    --L
//    输出 slv(R)-slv(L)
//    return 0
