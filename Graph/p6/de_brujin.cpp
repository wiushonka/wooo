#include <iostream>
#include <climits>
#include <unordered_set>
#include <vector>
using namespace std;
 
#define inf INT_MAX
 
unordered_set<string> used;
vector<char> edges;
 
void dfs(string node,int k,string al){
    for(int i=0;i<k;i++){
        string str=node+al[i];
        if(!used.count(str)){
            used.insert(str);
            dfs(str.substr(1),k,al);
            edges.push_back(al[i]);
        }
    }
}
 
string de_bruijn(int n,int k,string al){
    string start="";
    for(int i=0;i<n-1;i++){
        start+=al[0];
    }
 
    dfs(start,k,al);
    
    string res;
    for(auto x:edges){
        res+=x;
    }
    res+=start;
    
    return res;
}
 
int main(){
    int n,k;
    string alphabet="01";
    k=alphabet.length();
    cin>>n;
    cout<<de_bruijn(n,k,alphabet)<<endl;
    return 0;
}