#include<bits/stdc++.h>
using namespace std;
const int maxn = 10009;

int n;
bool A[maxn],B[maxn];

int main()
{
    cin>>n;
	char ch;
	for(int i=1;i<=n;++i){
		cin>>ch;
		A[i]=ch=='B'?0:1;
	}
	int mincnt=0x7fffffff,anslen;
	for(int len=1;len<=n;++len){
		memset(B,0,sizeof B);
		bool b=0,flag=1;
		int cnt=0;
		for(int i=1;i<=n;++i){
			b^=B[i];//数组B为记录差分的数组
			if(!(A[i]^b)){//若当前位置为0
				if(i+len-1>n){
                    flag=0;
                    break;
                }
				b^=1,B[i+len]^=1;
				++cnt;
			}
		}
		if(flag){
            if(cnt<mincnt)
                mincnt=cnt,anslen=len;
        }
	}
	cout<<anslen<<' '<<mincnt;
}
