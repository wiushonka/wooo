#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <stack>
 
using namespace std;
 
#define ll long long
#define inf LLONG_MAX
 
const int MAX_M=2e5+9;
vector<int> g[MAX_M];
vector<int> g_t[MAX_M];
int finish[MAX_M], scc_id[MAX_M];
bool used[MAX_M], res[MAX_M];
int t=0, scc_cnt=0;
vector<int> order;
 
void dfs(int u){
    used[u]=true;
    for(auto v:g[u]){
        if(!used[v]){
            dfs(v);
        }
    }
    order.push_back(u);
}   
 
void dfs1(int u){
    used[u]=true;
    scc_id[u]=scc_cnt;
    for(auto v:g_t[u]){
        if(!used[v]){
            dfs1(v);
        }
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        char f,s;
        int a,b;
        cin>>f>>a>>s>>b;
        if(f=='-') a=2*m-a+1;
        if(s=='-') b=2*m-b+1;
 
        g[2*m-a+1].push_back(b);
        g[2*m-b+1].push_back(a);
 
        g_t[b].push_back(2*m-a+1);
        g_t[a].push_back(2*m-b+1);
    }
 
    for(int i=1;i<=2*m;i++){
        if(!used[i]){
            dfs(i);
        }
    }
    
    reverse(order.begin(),order.end());
    fill(used,used+2*m+1,false);
    for(auto u:order){
        if(!used[u]){
            scc_cnt++;
            dfs1(u);
        }
    }
 
    for(int i=1;i<=m;i++){
        if(scc_id[i]==scc_id[2*m-i+1]){
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }
        res[i]=(scc_id[i]>scc_id[2*m-i+1]);
    }
 
    for(int i=1;i<=m;i++){
        cout<<(res[i]?'+':'-')<<" ";
    }
 
    return 0;
}