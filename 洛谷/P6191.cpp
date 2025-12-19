#include<bits/stdc++.h>
using namespace std;
int fn[100001],fg[100001],n,k;
int main(){
	cin>>n>>k;
	fn[1]=1;//先赋初值
	fg[1]=1;
	for(int i=2;i<=n;i++){
		fn[i]=(fn[i-1]+fg[i-1])%5000011;
		if(i>k+1){//上面的递推式
			fg[i]=(fg[i-k-1]+fn[i-k-1])%5000011;
		}
		else{
			fg[i]=1;
		}
	}
	cout<<(fg[n]+fn[n])%5000011<<endl;
	return 0;
}
