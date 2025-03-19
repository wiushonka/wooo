#include<algorithm>
#include<iostream>
#include<vector>
#include<climits>
#include<queue>
 
using namespace std;
 
#define ll long long
#define inf LLONG_MAX
 
const int mod=1e9+7;
const int MAX_N=1e5+9;
 
vector<int> g[MAX_N];
vector<int> rev_g[MAX_N];
bool used[MAX_N];
int start[MAX_N];
int finish[MAX_N];
int t;
vector<int> path;
 
void dfs1(int u){
    used[u]=true;
    path.push_back(u);
    for(int v:rev_g[u]){
        if(!used[v]){
            dfs1(v);
        }
    }
}
 
void dfs(int u){
    used[u]=true;
    start[u]=t++;
    for(int v:g[u]){
        if(!used[v]){
            dfs(v);
        }
    }
    finish[u]=t++;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        rev_g[v].push_back(u);    
    }
 
    t=0;
    for(int i=1;i<=n;i++){
        if(!used[i]){
            dfs(i);
        }
    }
 
    priority_queue<pair<int,int>> pq;
    for(int i=1;i<=n;i++){
        pq.push({finish[i],i});
    }
    fill(used,used+n+9,false);
    
    int scc=0;
    vector<int> kingdoms(n+9,0);
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();
        if(!used[u]){
            dfs1(u);
            scc++;
            while(!path.empty()){
                int v=path.back();
                path.pop_back();
                kingdoms[v]=scc;
            }
        }    
    }
    
    cout<<scc<<"\n";
    for(int i=1;i<=n;i++){
        cout<<kingdoms[i]<<" ";
    }
 
    return 0;
}