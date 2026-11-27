#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n;
stack<int>sta1;
stack<char>sta2;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int val;
        cin>>val;
        sta1.push(val);
    }
    for(int i=1;i<n;i++){
        char op;
        cin>>op;
        sta2.push(op);
    }
    for(int i=1;i<n;i++){
        int n1=sta1.top();
        sta1.pop();
        int n2=sta1.top();
        sta1.pop();
        char op=sta2.top();
        sta2.pop();
        int val=0;
        swap(n1,n2);
        if(op=='+'){
            val=n1+n2;
            sta1.push(val);
        }
        else if(op=='-'){
            val=n1-n2;
            sta1.push(val);
        }
        else if(op=='*'){
            val=n1*n2;
            sta1.push(val);
        }
        else{
            if(n2==0){
                cout<<"ERROR: "<<n1<<"/0"<<endl;
                return 0;
            }
            val=n1/n2;
            sta1.push(val);
        }
    }
    cout<<sta1.top()<<endl;
    return 0;
}