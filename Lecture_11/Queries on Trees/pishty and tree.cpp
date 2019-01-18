#include<iostream>
#define ll long long int 
#include<string>
using namespace std;
#include<vector>
#include<algorithm>
vector<ll> st(1000005),tour,et(1000005),w,q1,q2,s(1000005),mytour(1000005),st2(1000005);
vector<vector<pair<ll,ll> > > adj(1000005);
vector<pair<ll,ll> > arr,edge;
vector<ll> tree(1000005),lazy(1000005);

ll queryRange(ll node, ll start, ll end, ll l, ll r)
{
    if(start > end || start > r || end < l)
        return 0;         // Out of range
    if(lazy[node] != 0)
    {
        // This node needs to be updated
        tree[node] = tree[node]^lazy[node];            // Update it
        if(start != end)
        {
            lazy[node*2] = lazy[node*2]^lazy[node];         // Mark child as lazy
            lazy[node*2+1] = lazy[node*2+1]^lazy[node];    // Mark child as lazy
        }
        lazy[node] = 0;                 // Reset it
    }
    if(start >= l && end <= r)             // Current segment is totally within range [l, r]
        return tree[node];
    ll mid = (start + end) / 2;
    ll p1 = queryRange(node*2, start, mid, l, r);         // Query left child
    ll p2 = queryRange(node*2 + 1, mid + 1, end, l, r); // Query right child
    return (p1^p2);
}

/*
ll  query(ll node, ll start, ll end, ll l, ll r)
{
    if(r < start || end < l)
    {
        // range represented by a node is completely outside the given range
        return 0;
    }
    if(l <= start&&end <= r)
    {
        // range represented by a node is completely inside the given range
        return tree[node];
    }
    // range represented by a node is partially inside and partially outside the given range
    ll mid = (start + end) / 2;
    ll p1 = query(2*node, start, mid, l, r);
    ll p2 = query(2*node+1, mid+1, end, l, r);
    return (p1 ^ p2);
}
*/

void build(int node, int start, int end)
{
    if(start == end)
    {
        // Leaf node will have a single element
        tree[node] = mytour[start];

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
           // cout<<"\n my node in tree "<<node<<" "<<tree[node];
}

void updateRange(ll node, ll start, ll end, ll l, ll r,ll val)
{
    if(lazy[node] != 0)
    { 
        // This node needs to be updated
        tree[node] =tree[node]^lazy[node];    // Update it
        if(start != end)
        {
            lazy[node*2] = lazy[node*2]^lazy[node];                  // Mark child as lazy
            lazy[node*2+1] = lazy[node*2+1]^lazy[node];                // Mark child as lazy
        }
        lazy[node] = 0;                                  // Reset it
    }
    if(start > end || start > r || end < l)              // Current segment is not within range [l, r]
        return;
    if(start >= l && end <= r)
   
    {
        // Segment is fully within range
        tree[node] = tree[node]^val;
        if(start != end)
        {
            // Not leaf node
            lazy[node*2] = lazy[node*2] ^val;
            lazy[node*2+1] = lazy[node*2+1]^val;
        }
        return;
    }
    ll mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);        // Updating left child
    updateRange(node*2 + 1, mid + 1, end, l, r, val);   // Updating right child
    tree[node] = tree[node*2] ^ tree[node*2+1];        // Updating root with max value 
}
/*
void updateRange(ll node, ll start, ll end, ll l, ll r, ll val)
{
    // out of range
    if (start > end || start > r || end < l)
        return;

    // Current node is a leaf node
    if (l<=start&&end<=r&&(start==end))
    {
        // Add the difference to current node
        tree[node] = tree[node]^val;
        mytour[start]=tree[node];
        return;
    }

    // If not a leaf node, recur for children.
    ll mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);
    updateRange(node*2 + 1, mid + 1, end, l, r, val);

    // Use the result of children calls to update this node
    tree[node] = tree[node*2]^tree[node*2+1];
}
*/


void dfs(ll node,ll parent,ll &timer,ll &timer2)
{
    timer++;
    timer2++;
    st2[node]=timer2;
    st[node]=timer;
    ll i;
    //tour.push_back(node);
    for(i=0;i<adj[node].size();i=i+1)
    {
        if(adj[node][i].first!=parent)
        {
            dfs(adj[node][i].first,node,timer,timer2);
            //tour.push_back(node);
        }
    }
    timer++;
    et[node]=timer;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin>>t;
    while(t--)
    {
        arr.clear();
        edge.clear();
        w.clear();
        adj.clear();
        q1.clear();
        q2.clear();
        st.clear();
        et.clear();
        st2.clear();
        tree.clear();
        mytour.clear();
        tour.clear();
        lazy.clear();

        lazy.resize(1000005);
        adj.resize(1000005);
        st.resize(1000005);
        et.resize(1000005);
        st2.resize(1000005);
        tree.resize(1000005);
        mytour.resize(1000005);
       
        ll n,u,v,c,i;
        cin>>n;
        for(i=0;i<n-1;i=i+1)
        {
           cin>>u>>v>>c;
           adj[u].push_back(make_pair(v,c));
           adj[v].push_back(make_pair(u,c));
           edge.push_back(make_pair(u,v));
           w.push_back(c);
        }
        ll timer=0,timer2=0;
        dfs(1,-1,timer,timer2);
        for(i=0;i<n-1;i=i+1)
        {
            if(st[edge[i].first]<st[edge[i].second])
            swap(edge[i].first,edge[i].second);
            //cout<<st[edge[i].first]<<" ";
            arr.push_back(make_pair(w[i],-edge[i].first));
        }
     ///   cout<<"\n";
        ll m;
        cin>>m;
        for(i=1;i<=m;i=i+1)
        {
            cin>>u>>v>>c;
            q1.push_back(u);
            q2.push_back(v);
            arr.push_back(make_pair(c,i));
        }
        vector<ll> ans(m+1);
        sort(arr.begin(),arr.end());
        ll l,r;
    
        ll k,rn,m2=m;
        //build(1,1,n);
        for(i=0;i<arr.size();i=i+1)
        {
            //cout<<arr[i].second<<"  **** \n";
            if(arr[i].second<0)
            {
                l=st[-arr[i].second];
                r=et[-arr[i].second];
                rn=(r-l-1)/2+st2[-arr[i].second];
                //cout<<st2[-arr[i].second]<<" "<<rn<<"===\n";
                //cout<<"----/// "<<st2[q1[-arr[i].second]]<<" "<<st2[q2[-arr[i].second]]<<" "<<arr[i].first<<"\n";
                updateRange(1,1,n,st2[-arr[i].second],rn,arr[i].first);
                /*for(k=1;k<=n;k=k+1)
                {
                    if(k>=st2[-arr[i].second]&&k<=rn)
                    {
                        mytour[k]=mytour[k]^arr[i].first;
                    }
                }*/
                /*for(k=1;k<=2*maximum-1;k=k+1)
                {
                    cout<<tree[k]<<" ";
                }*/
                //cout<<"\n";
            }
            else
            {
                //cout<<"---- "<<st2[q1[arr[i].second-1]]<<" "<<st2[q2[arr[i].second-1]]<<" "<<arr[i].first<<"\n";
                ll x1=queryRange(1,1,n,st2[q1[arr[i].second-1]],st2[q1[arr[i].second-1]]);
                ll x2=queryRange(1,1,n,st2[q2[arr[i].second-1]],st2[q2[arr[i].second-1]]);
                ans[arr[i].second]=x1^x2;
                //cout<<(s[q1[arr[i].second]]^s[q2[arr[i].second]])<<"\n";
                //ans[arr[i].second]=mytour[st2[q1[arr[i].second-1]]]^mytour[st2[q2[arr[i].second-1]]];
                if(m==0)
                {
                    break;
                }
                m=m-1;
            }
        }
       for(i=1;i<=m2;i=i+1)
        cout<<ans[i]<<"\n";

    
    }
    return 0;
}
