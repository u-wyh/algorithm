#include<iostream>
#include<vector>

using namespace std;

int n,m,tmp;

int main()
{
    vector<int>stu(11,0);
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&tmp);
        stu.push_back(tmp);
    }
    stu[0]=2;
    for(int i=0;i<m;i++){
        cin>>tmp;
        printf("%d\n",stu[tmp-1]);
    }
    cout<<stu.size()<<"\n";
    return 0;
}
