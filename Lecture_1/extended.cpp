ll x,y;
template<class T> T gcd(T a,T b)
{  
    if(a==0)
    {
        x=0,y=1; return b;
    }
    T gc=gcd(b%a,a);
    T temp;
    temp=x;
    x=y-(b/a)*temp;
    y=temp;
    return gcd;
}
