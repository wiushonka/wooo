#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <unordered_set>
#include <cstring>
using namespace std;

#define ll long long
#define inf LLONG_MAX
#define _inf LLONG_MIN

const int MAX_N=1e5+9;
int coins[MAX_N];
vector<int> g[MAX_N];
vector<int> g_t[MAX_N];
vector<int> order;
bool used[MAX_N];
ll scc_w[MAX_N];
int scc[MAX_N];
vector<int> sccs[MAX_N];
int scc_cnt=0;
unordered_set<int> g_scc[MAX_N];
ll dp[MAX_N];

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
    scc_w[scc_cnt]+=coins[u];
    scc[u]=scc_cnt;
    sccs[scc_cnt].push_back(u);
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
    for(int i=1;i<=n;i++){
        cin>>coins[i];
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g_t[v].push_back(u);
    }

    for(int i=1;i<=n;i++){
        if(!used[i]){
            dfs(i);
        }
    }

    reverse(order.begin(),order.end());
    memset(used,false,sizeof(used));

    for(int i=0;i<order.size();i++){
        int u=order[i];
        if(!used[u]){
            scc_cnt++;
            dfs1(u);
        }
    }

    for(int i=1;i<=scc_cnt;i++){
        for(auto u:sccs[i]){
            for(auto v:g[u]){
                if(scc[u]!=scc[v]){
                    g_scc[scc[u]].insert(scc[v]);
                }
            }
        }
    }

    memset(dp,0,sizeof(dp));
    for(int i=1;i<=scc_cnt;i++){
        dp[i]=scc_w[i];
    }   

    bool used_scc[MAX_N];
    vector<int> order_scc;
    memset(used_scc,false,sizeof(used_scc));
    for(int i=0;i<order.size();i++){
        int u=order[i];
        if(!used_scc[scc[u]]){
            used_scc[scc[u]]=true;
            order_scc.push_back(scc[u]);
        }
    }
    
    for(int i=0;i<order_scc.size();i++){
        int comp=order_scc[i];
        for(auto con:g_scc[comp]){
            dp[con]=max(dp[con],dp[comp]+scc_w[con]);
        }
    }

    ll res=-1;
    for(int i=1;i<=scc_cnt;i++){
        res=max(res,dp[i]);
    }
    cout<<res<<endl;

    return 0;
}
