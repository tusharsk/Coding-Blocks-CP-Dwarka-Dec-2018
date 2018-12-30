#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;
using namespace std;
 
#define pb push_back
#define f first
#define s second
#define mp make_pair
#define SZ(x) ((int)(x.size()))
#define FOI(i, a, n) for( i = int(a); i <= int(n); i++)
#define FOD(i, a, n) for( i = int(a); i >= int(n); i--)
#define IN(x, y) ((y).find(x) != (y).end())
#define ALL(t) t.begin(),t.end()
#define MSET(tabl,i) memset(tabl, i, sizeof(tabl))
#define PSET(x,y) fixed<<setprecision(y)<<lf(x)
#define DBG(c) cout << #c << " = " << c << endl;
#define RTIME ((double)clock()/(double)CLOCKS_PER_SEC)
#define sync ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define Mod 1000000000
 
typedef long long int  ll;
typedef long double lf;
typedef pair < ll, ll > pii;
typedef pair < ll, ll > pll;
typedef vector < ll > vi;
typedef vector<vi> vvi;
typedef complex<double> base;
 
#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template <typename Arg1> 
    void __f(const char* name, Arg1&& arg1){
        cout << name << " : " << arg1 << std::endl;
        //use cerr if u want to display at the bottom
    }
    template <typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
    }
#else
#define trace(...)
#endif
 
const int N = 1e5 + 5;
const int lgN = 1e6+5;
const int te = 3e8+1;
const ll MOD = 998244353;
const lf pi = 3.141592653589793238462643383;
const ll IMAX = 1e9 + 5; 
const double PI = 3.141592653589793;
 
 
template<class T>
using max_pq = priority_queue<T>;
template<class T>
using min_pq = priority_queue<T,vector<T>,greater<T>>; 
template<class T>
using OST = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
ll x,y;
template<class T> T gcd(T a,T b){ if(a==0) {x=0,y=1; return b;}T gc=gcd(b%a,a);T temp;temp=x;x=y-(b/a)*temp;y=temp;return gc;}
 
//(a^x)%m
ll po(ll a, ll x,ll m){ if(x==0){return 1;}ll ans=1;ll k=1;  while(k<=x) {if(x&k){ans=((ans*a)%m);} k<<=1; a*=a; a%=m; }return ans; } 
 
ll modInverse(ll A, ll M)
{
    gcd(A,M);
    return (x%M+M)%M;    //x may be negative
}
 

vvi multiply(vvi a,vvi b,ll k)
{
    ll i,j,x;

    vvi ans(k,vi (k));
    //trace(k);
   
    FOI(i,0,k-1)
    {
        FOI(j,0,k-1)
        {
            FOI(x,0,k-1)
            ans[i][j]=(ans[i][j]+(a[i][x]*b[x][j])%Mod)%Mod;
        }
    }

    return ans;
}

vector<vector<ll> > expo(vvi &v,ll p,ll k)
{

    vvi res(k,vi (k));
    
    ll i,j;

    FOI(i,0,k-1)
    res[i][i]=1;

    
    
    while(p>0)
    {
        
        
        if(p&1)
        {
            res=multiply(res,v,k);
        }

        v=multiply(v,v,k);

        p=p/2;

    }
    return res;
    
}

ll fuc(vvi &v,vi &b,ll n,ll k)
{
    if(n<=k)
    return b[n-1]%Mod;

    ll i,j;
    vector<vector<ll> > ans=expo(v,n-k,k);
    
    ll cou=0;
    FOI(i,0,k-1)
    {
        cou=(cou+(ans[0][i]*b[k-1-i])%Mod)%Mod;
    }

    return cou;
}

int main()
{
    ll t;
    cin>>t;
    while(t--)
    {
        ll k,i,j;
        cin>>k;
        vi a(k),b(k);  
        for(i=0;i<k;i=i+1)
        cin>>b[i];
       
        
        vector<vector<ll> > v(k,vector<ll> (k));
        FOI(i,0,k-1)
        {
            cin>>a[i];
            v[0][i]=a[i]%Mod;
        }
        j=0;
        FOI(i,1,k-1)
        {
            v[i][j]=1;
            j++;
        }
       
        ll n;
        cin>>n;
       // trace(n);
        ll ans=fuc(v,b,n,k);
        cout<<ans<<"\n";
    }
    return 0;

}