#include <bits/stdc++.h>
using namespace std;

stack <int> st;
int t[300005],m[300005];
long long ans;

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t[i];
		if(t[i]<i){
			cout<<-1;
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		cin>>m[i];
	}
	int dw=n;
	for(int i=t[n];i>=1;i--){
		if(t[dw]<i){
        //当下一个人还没来取果汁时，就可以先制作后面的
			if(st.size()){
				ans+=st.top();
				st.pop();
			}
		}else if(t[dw]==i){
        //当下一个人已经来取果汁时，就立刻制作他的
			if(st.size())
                st.push(max(st.top(),m[dw]));
			else
                st.push(m[dw]);
			dw--,i++;
		}else if(t[dw]>i)
            dw--,i++;
      //当下一个人和上一个人同时取果汁时就要存到栈里提前制作。
	}

	while(st.size()){
		ans+=st.top();
		st.pop();
	}
	cout<<ans;
	return 0;
}
