#include<bits/stdc++.h>
using namespace std;

int n,m;
string st[50100][30];

void upr(char &x){
	if ('a'<=x && x<='z')
        x-=32;
}

string mx(string a,string b){
	string x=a,y=b;
	for(int i=0;i<a.size();i++) upr(x[i]);
	for(int i=0;i<b.size();i++) upr(y[i]);
	return x>y?a:b;
}

string ask(int l,int r){
	int lc=log2(r-l+1);//区间长度求log
	return mx(st[l][lc],st[r-(1<<lc)+1][lc]);
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		char x[20];
		scanf("%s",x);
		st[i][0]=x;
		//边界条件
	}
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<(j-1))<=n;i++){
			st[i][j]=mx(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
	while(m--){
		int l,r;
		cin>>l>>r;
		//printf("%s\n",ask(l,r).c_str());
		cout<<ask(l,r)<<endl;
	}
	return 0;
}
