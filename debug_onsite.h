// ============= Include this =============
// #ifdef LOCAL
// #include "debug.h"
// #else
// #define dg(x...)
// #endif
void __p(bool x)          { cerr<<(x?"1":"0"); }
void __p(char x)          { cerr<<x; }
void __p(int x)           { cerr<<x; }
void __p(long long x)     { cerr<<x; }
void __p(double x)        { cerr<<x; }
void __p(const string& x) { cerr<<'"'<<x<<'"'; }

// forward declare before pair so pair<A, vector<B>> can find it
template<class T> void __p(const T& x);

template<class A,class B>
void __p(const pair<A,B>& x){ cerr<<"("; __p(x.first); cerr<<","; __p(x.second); cerr<<")"; }

template<class T>
void __p(const T& x){
    cerr<<"{"; bool f=0;
    for(auto i:x){ if(f)cerr<<","; __p(i); f=1; }
    cerr<<"}";
}

void   __db(const char* n){ cerr<<"\n"; }
template<class T,class...R>
void __db(const char* n, T v, R...r){
    while(*n==' ')n++;
    const char* c=strchr(n,',');
    cerr<<string(n,c?c-n:strlen(n))<<" = "; __p(v); cerr<<" | ";
    __db(c?c+1:"",r...);
}
#define dg(...) cerr << "[" << __LINE__ << "] ",__db(#__VA_ARGS__,__VA_ARGS__)

