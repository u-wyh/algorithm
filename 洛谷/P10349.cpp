#include<iostream>
using namespace std;
int n,lans,rans,l[300001],r[300001];
char c[300001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
        cin>>c[i];
	for(int i=1;i<=n;i++){
		l[i]=lans;
		if(c[i]=='P')
            lans++;
	}
	for(int i=n;i>=1;i--){
		r[i]=rans;
		if(c[i]=='L')
            rans++;
	}
	for(int i=1;i<=n;i++){
		if(l[i]==r[i])
            cout<<l[i]+r[i];
		else if(l[i]<r[i]){
			if(c[i]=='L')cout<<l[i]*2;
			else cout<<l[i]*2+1;
		}
		else{
			if(c[i]=='P')cout<<r[i]*2;
			else cout<<r[i]*2+1;
		}
		cout<<" ";
	}
	return 0;
}
