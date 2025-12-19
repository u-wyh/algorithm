#include<bits/stdc++.h>
using namespace std;

int pos[7];

int main()
{
    int T;
    cin>>T;
    while(T--){
        char c;
        cin>>c>>pos[1]>>pos[2]>>pos[3]>>pos[4]>>pos[5]>>pos[6];
        if ((c=='W')&& ((pos[3]-pos[2]==1&&pos[2]-pos[1]>1)||(pos[5]-pos[4]==1&&pos[6]-pos[5]>1))
            &&(!(pos[3]-pos[2]==1&&pos[5]-pos[4]==1)))
			 std::cout<<"Yes\n";
		else std::cout<<"No\n";
    }
    return 0;
}
