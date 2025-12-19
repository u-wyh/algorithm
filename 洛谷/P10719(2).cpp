#include<iostream>
using namespace std;
bool a[114][514];// 存储输入
int b[1919][810];// 存储二维前缀和
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,m,k;cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;cin>>c;
			a[i][j]=c-'0';
			b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];// 利用容斥原理计算出 b[i][j]
		}
	}
	int mn=0xcff0102;// 一个足够大的数
	for(int x1=0;x1<n;x1++){// 注意这里的范围
		for(int y1=0;y1<m;y1++){// 注意这里的范围
			for(int x2=x1;x2<=n;x2++){
				for(int y2=y1;y2<=m;y2++){
					int tmp=b[x2][y2]-b[x2][y1]-b[x1][y2]+b[x1][y1];// 左上端点为 (x1+1,y1+1)，右上端点为 (x2+1,y2+1) 的矩形中 1 的数量
					if(tmp>=k)mn=min(mn,(x2-x1)*(y2-y1));
				}
			}
		}
	}
	cout<<((mn==0xcff0102)?0:mn);// 注意判断无解
	return 0;
}
