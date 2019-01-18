#include<iostream>
#define ll long long int 
#include<string>
using namespace std;
#include<vector>
#include<set>
#include<algorithm>
#include <iomanip>
#include<map>
#include<cmath>

#include<limits.h>
#define MOD 1000000007
ll bs;
vector<ll> block(105);
vector<ll> dp;
vector<vector<ll> > srd(105,vector<ll> (1050000));
void build(vector<ll> &v)
{
    ll i,x=0;
    for(i=0;i<v.size();i=i+1)
    {
        if(i%bs==0)
        {
            x=v[i];
            dp[i]=v[i];
        }
        else
        {
            x=x^v[i];
            dp[i]=dp[i-1]^v[i];
        }
        srd[i/bs][x]++;
    }
}
 
void update(ll index,ll value,vector<ll> &v)
{
    ll bn=index/bs,i;
    for(i=index;i<bn*bs+bs&&i<v.size();i=i+1)
    {
        srd[bn][dp[i]]--;
        dp[i]=dp[i]^v[index]^value;
        srd[bn][dp[i]]++;
    }
    block[bn]=block[bn]^v[index]^value;
    v[index]=value;
}
ll query(ll index,ll k,vector<ll> &v)
{
    ll cou=0,i;
    ll last=index/bs;
    //cout<<last<<"\n";
    for(i=0;i<last;i=i+1)
    {
           
        if(srd[i][k]>0)
           cou=srd[i][k]+cou;
        
        k=k^block[i];
    }
    //cout<<cou<<"\n";
    i=bs*(i);
    //cout<<i<<"\n";
    for(;i<=index;i=i+1)
    {
        //cout<<v[i]<<" "<<k<<"\n";
        if(v[i]==k)
        {
            cou=cou+1;
           // cout<<"p\n";
            
            
        }
        k=k^v[i];
    }
    return cou;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,q,i;
    cin>>n>>q;
    vector<ll> v(n);
    bs=1000;
    dp.resize(n);
    for(i=0;i<n;i=i+1)
    {
        cin>>v[i];
        //cout<<v[i]<<"\n";
        block[i/bs]=block[i/bs]^v[i];
        //cout<<i/bs<<" "<<block[i/bs]<<"\n";
    }
    
    build(v);
    
    while(q--)
    {
        ll x,cou,t;
        cin>>t>>i>>x;
        if(t==1)
        update(i-1,x,v);
        else
        {
            cou=query(i-1,x,v);
            cout<<cou<<"\n";
        }
       
    
    }
    return 0;
}
