#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=1e5+9;
vector<int> g[N];
vector<int> g_t[N];
int in_d[N];
int out_d[N];
vector<int> order;
bool used[N];
vector<int> path;
vector<int> circuit;

void hierholzer(int start){
    path.push_back(start);

    while(path.size()>0){
        int u=path.back();
        if(g[u].size()>0){
            int v=g[u].back();
            g[u].pop_back();
            path.push_back(v);
        }else{  
            path.pop_back();
            circuit.push_back(u);
        }
    }
    reverse(circuit.begin(),circuit.end());
}

void dfs1(int u){
    used[u]=true;
    for(auto v:g[u]){
        if(!used[v]){
            dfs1(v);
        }
    }
    order.push_back(u);
}

void dfs2(int u){
    used[u]=true;
    for(auto v:g_t[u]){
        if(!used[v]){
            dfs2(v);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n,m;
    cin>>n>>m;
    while(m--){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g_t[v].push_back(u);
        out_d[u]++;
        in_d[v]++;
    }

    int an=-1,bn=-1;
    for(int i=1;i<=n;i++){
        if(out_d[i]+1==in_d[i]){
            if(bn!=-1){
                cout<<"IMPOSSIBLE\n";
                return 0;    
            }else{
                bn=i;
            }
        }else if(out_d[i]==in_d[i]+1){
            if(an!=-1){
                cout<<"IMPOSSIBLE\n";
                return 0;    
            }else{
                an=i;
            }
        }else if(out_d[i]!=in_d[i]){
            cout<<"IMPOSSIBLE\n";
            return 0;
        }
    }

    if(an!=1 || bn!=n){
        cout<<"IMPOSSIBLE\n";
        return 0;
    }
    g[bn].push_back(an);
    g_t[an].push_back(bn);

    for(int i=1;i<=n;i++){
        if(!used[i]){
            dfs1(i);
        }
    }

    reverse(order.begin(),order.end());
    memset(used,false,sizeof(used));

    int valid_scc_cnt=0;
    for(auto u:order){
        if(!used[u] && (out_d[u]!=0 || in_d[u]!=0)){
            valid_scc_cnt++;
            dfs2(u);
        }
    }

    if(valid_scc_cnt>1){
        cout<<"IMPOSSIBLE\n";
        return 0;
    }

    hierholzer(1); 
    
    vector<vector<int>> path(n+1);
    bool additional_edge_removed=false;
    for(int i=0;i<circuit.size()-1;i++){
        int u,v;
        v=circuit[i];
        u=circuit[i+1];
        if(!additional_edge_removed && u==an && v==bn){
            additional_edge_removed=true;
            continue;
        }
        path[u].push_back(v);
    }

    int x=bn;
    vector<int> res;
    res.push_back(x);
    while(!path[x].empty()){
        res.push_back(path[x].back());        
        path[x].pop_back();
        x=res.back();
    }
    
    reverse(res.begin(),res.end());
    
    for(auto x:res){
        cout<<x<<" ";
    }

    return 0;
}