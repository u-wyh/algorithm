#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;

int n,color[N];
map<int,int> last;

int main()
{
    cin>>n;
	for(int i=1;i<=n;i++){
        cin>>color[i];
		last[color[i]]=i;
	}
	for(int i=1;i<=n;i++){
		int lci=last[color[i]];
		for(int j=i+1;j<lci;j++)
            color[j]=color[i];
		i=lci;
	}
	for(int i=1;i<=n;i++)
        printf("%d\n",color[i]);
	return 0;
}
