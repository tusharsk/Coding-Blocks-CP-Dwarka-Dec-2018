#include<iostream>
#define ll long long int 
#include<string>
using namespace std;
#include<vector>
#include<set>
#include<algorithm>
#define MOD 1000000007
#include<cmath>
#include<cstring>
#include<cstdio>
vector<vector<ll> > adj(1000000);
vector<ll> len(1000000),a,v(1000000),start(1000000);
vector<ll> tree(1000000),lazy(1000000);


void updateRange(ll node, ll start, ll end, ll l, ll r, ll val)
{
    if(lazy[node] != 0)
    { 
        // This node needs to be updated
        tree[node] += (end - start + 1) * lazy[node];    // Update it
        if(start != end)
        {
            lazy[node*2] += lazy[node];                  // Mark child as lazy
            lazy[node*2+1] += lazy[node];                // Mark child as lazy
        }
        lazy[node] = 0;                                  // Reset it
    }
    if(start > end || start > r || end < l)              // Current segment is not within range [l, r]
        return;
    if(start >= l && end <= r)
    {
        // Segment is fully within range
        tree[node]= val;
        if(start != end)
        {
            // Not leaf node
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    ll mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);        // Updating left child
    updateRange(node*2 + 1, mid + 1, end, l, r, val);   // Updating right child
    tree[node] = tree[node*2] + tree[node*2+1];        // Updating root with max value 
}



void build(ll node, ll start, ll end)
{
    if(start == end)
    {
        // Leaf node will have a single element
        tree[node] = a[start];
    }
    else
    {
        ll mid = (start + end) / 2;
        // Recurse on the left child
        build(2*node, start, mid);
        // Recurse on the right child
        build(2*node+1, mid+1, end);
        // Internal node will have the sum of both of its children
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}


ll queryRange(ll node, ll start, ll end, ll l, ll r)
{
    if(start > end || start > r || end < l)
        return 0;         // Out of range
    if(lazy[node] != 0)
    {
        // This node needs to be updated
        tree[node] += (end - start + 1) * lazy[node];            // Update it
        if(start != end)
        {
            lazy[node*2] += lazy[node];         // Mark child as lazy
            lazy[node*2+1] += lazy[node];    // Mark child as lazy
        }
        lazy[node] = 0;                 // Reset it
    }
    if(start >= l && end <= r)             // Current segment is totally within range [l, r]
        return tree[node];
    ll mid = (start + end) / 2;
    ll p1 = queryRange(node*2, start, mid, l, r);         // Query left child
    ll p2 = queryRange(node*2 + 1, mid + 1, end, l, r); // Query right child
    return (p1 + p2);
}


ll dfs(ll node,ll parent)
{
    ll i,x=0;
    a.push_back(v[node]);
    start[node]=a.size()-1;
    for(i=0;i<adj[node].size();i=i+1)
    {
        if(adj[node][i]!=parent)
        {
            x=x+dfs(adj[node][i],node)+1;
        }
    }
    len[node]=x;
    return x;
}


int main()
{
    ll n,m;
    cin>>n>>m;
    ll i,u,vt;
    for(i=1;i<=n;i=i+1)
    {
        cin>>v[i];
    }
    for(i=0;i<n-1;i=i+1)
    {
        cin>>u>>vt;
        adj[u].push_back(vt);
        adj[vt].push_back(u);
    }
    ll x=dfs(1,-1);
    len[1]=x;
    build(1,0,a.size()-1);
    ll l,r,s;
    while(m--)
    {
        
        char ch;
        cin>>ch;
        if(ch=='Q')
        {
            //cout<<m<<"***";
            cin>>s;
            
            l=start[s];
            r=l+len[s];
            ll cou=queryRange(1,0,a.size()-1,l,r);
            cout<<cou<<"\n";
        }
        else
        {
            //cout<<m<<"+++++";
            cin>>s>>x;
            updateRange(1,0,a.size()-1,start[s],start[s],x);
        }
        
    }
    return 0;
}


