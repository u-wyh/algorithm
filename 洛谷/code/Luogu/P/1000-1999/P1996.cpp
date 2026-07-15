#include<queue>
#include<iostream>

using namespace std;

int n,k;
queue<int>q;

void work(){
    int i;
    for(int i=1;i<=n;i++)
        q.push(i);
    while(q.size()){
        for(int i=1;i<k;i++){
            q.push(q.front());
            q.pop();
        }
        printf("%d ",q.front());
        q.pop();
    }
}

int main(){
    cin>>n>>k;
    work();
    return 0;
}
