// https://www.luogu.com.cn/problem/P5266
// 题意：维护学生姓名到成绩的映射，支持 Q 次操作：1 NAME SCORE 插入或更新成绩输出 OK；
// 2 NAME 查询成绩（无则输出 Not found）。
// 3 NAME 删除学生（成功输出 Deleted successfully，无则输出 Not found）；4 输出当前学生总数。
// 数据范围：1 <= Q <= 10^5，姓名长度不超过 20（字母数字、区分大小写），0 < SCORE < 2^31。
#include<bits/stdc++.h>
// 算法标签：map
using namespace std;

int n,opt,num,ans;
string name;
map<string ,int >ds;

int main()
{
    cin>>n;
    while(n--){
        cin>>opt;
        if(opt==1){
            cin>>name>>num;
            ds[name]=num;
            cout<<"OK"<<endl;
        }else if(opt ==2){
            cin>>name;
            if(ds.find(name)!=ds.end())
                cout<<ds[name]<<endl;
            else
                cout<<"Not found"<<endl;
        }else if(opt==3){
            cin>>name;
            if(ds.find(name)!=ds.end()){
                ds.erase(ds.find(name));
                cout<<"Deleted successfully"<<endl;
            }else
                cout<<"Not found"<<endl;
        }else
            cout<<ds.size()<<endl;
    }
    return 0;
}
