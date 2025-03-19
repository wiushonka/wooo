#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <unordered_set>
#include <cstring>
#include <stack>
using namespace std;
 
#define ll long long
#define inf LLONG_MAX
#define _inf LLONG_MIN
 
const int MAX_N=1e5+9;
unordered_set<int> g[MAX_N];
int degree[MAX_N];
bool used[MAX_N];
stack<int> current_path;
vector<int> circuit;
 
void dfs(int u){
    used[u]=true;
    for(auto v:g[u]){
        if(!used[v]){
            dfs(v);
        }
    }
}
 
void euler_circuit(int start){
    current_path.push(start);
    while(!current_path.empty()){
        int u=current_path.top();
 
        if(!g[u].empty()){
            int v=*(g[u].begin());
            g[u].erase(g[u].begin());
            g[v].erase(g[v].find(u));
            current_path.push(v);
        }else{
            circuit.push_back(u);
            current_path.pop();
        }
    }
}
 
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n,m;
    cin>>n>>m;
    while(m--){
        int u,v;
        cin>>u>>v;
        degree[u]++;
        degree[v]++;
        g[u].insert(v);
        g[v].insert(u);
    }
 
    int odd=0;
    for(int i=1;i<=n;i++){
        if(degree[i]%2!=0){
            odd++;
        }
    }
    if(odd>0){
        cout<<"IMPOSSIBLE\n";
        return 0;
    }
 
    dfs(1);
    for(int i=1;i<=n;i++){
        if(degree[i]!=0 && !used[i]){
            cout<<"IMPOSSIBLE\n";
            return 0;
        }
    }
 
    euler_circuit(1);
    reverse(circuit.begin(),circuit.end());
    for(auto u:circuit){
        cout<<u<<" ";
    }
 
    return 0;
}