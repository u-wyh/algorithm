#include<bits/stdc++.h>
using namespace std;

int n,d=1;
deque<int >Deque;

int main()
{
    cin>>n;
    char a,b;
    int c;
    while(n--){
        cin>>a;
        if(a=='A'){
            cin>>b;
            if(b=='L')
                Deque.push_front(d);
            else if(b=='R')
                Deque.push_back(d);
            d++;
        }else{
            cin>>b>>c;
            if(b=='L'){
                while(c--){
                    Deque.pop_front();
                }
            }else{
                while(c--){
                    Deque.pop_back();
                }
            }
        }
    }
    for(int a:Deque)
        cout<<a<<endl;
    return  0;
}
