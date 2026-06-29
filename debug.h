// ===================== Minimal universal debug printer =====================
// Usage: dg(x);  dg(x, y, z);   prints:  x = <val> | y = <val> | z = <val>
// Works on: all primitives, string, pair, tuple, and ANY container
// (vector, set, map, deque, array, multiset, unordered_*, nested combos, etc.)
// NOTE: this file assumes `using namespace std;` is already active (normal in
// a single-file ICPC setup with #include <bits/stdc++.h> + using namespace std;
// above the #include of this header).

template <typename T, typename = void>
struct is_iterable : false_type {};

template <typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T&>())), decltype(end(declval<T&>()))>> : true_type {};

// Forward declarations FIRST -- required so every __print overload can see every
// other overload regardless of definition order (two-phase name lookup).
void __print(bool x);
void __print(char x);
void __print(const char* x);
void __print(const string& x);

template <typename T> typename enable_if<is_arithmetic<T>::value && !is_same<T,bool>::value && !is_same<T,char>::value>::type __print(T x);
template <typename T1, typename T2> void __print(const pair<T1, T2>& p);
template <typename... Ts> void __print(const tuple<Ts...>& t);
template <typename T> typename enable_if<is_iterable<T>::value>::type __print(const T& v);
template <typename T> void __print(stack<T> s);
template <typename T> void __print(queue<T> q);
template <typename T, typename C> void __print(priority_queue<T, C> pq);

// ---- Definitions ----

void __print(bool x)              { cerr << (x ? "1" : "0"); }
void __print(char x)              { cerr << '\'' << x << '\''; }
void __print(const char* x)       { cerr << '"' << x << '"'; }
void __print(const string& x)     { cerr << '"' << x << '"'; }

template <typename T>
typename enable_if<is_arithmetic<T>::value && !is_same<T,bool>::value && !is_same<T,char>::value>::type
__print(T x) { cerr << x; }

template <typename T1, typename T2>
void __print(const pair<T1, T2>& p) {
    cerr << '('; __print(p.first); cerr << ", "; __print(p.second); cerr << ')';
}

template <size_t I = 0, typename... Ts>
void __pr_tuple(const tuple<Ts...>& t) {
    if constexpr (I < sizeof...(Ts)) {
        if constexpr (I > 0) cerr << ", ";
        __print(get<I>(t));
        __pr_tuple<I + 1>(t);
    }
}
template <typename... Ts>
void __print(const tuple<Ts...>& t) { cerr << '('; __pr_tuple(t); cerr << ')'; }

// Generic container (vector, set, map, deque, array, multiset, unordered_*, ...)
template <typename T>
typename enable_if<is_iterable<T>::value>::type
__print(const T& v) {
    cerr << '{';
    bool first = true;
    for (const auto& x : v) {
        if (!first) cerr << ", ";
        first = false;
        __print(x);
    }
    cerr << '}';
}

// stack / queue / priority_queue (not iterable, need draining a copy)
template <typename T>
void __print(stack<T> s) {
    vector<T> tmp;
    while (!s.empty()) { tmp.push_back(s.top()); s.pop(); }
    reverse(tmp.begin(), tmp.end());
    __print(tmp);
}
template <typename T>
void __print(queue<T> q) {
    vector<T> tmp;
    while (!q.empty()) { tmp.push_back(q.front()); q.pop(); }
    __print(tmp);
}
template <typename T, typename C>
void __print(priority_queue<T, C> pq) {
    vector<T> tmp;
    while (!pq.empty()) { tmp.push_back(pq.top()); pq.pop(); }
    __print(tmp);
}

void __dbg(const char* names) { cerr << "\n"; (void)names; }

template <typename T, typename... Rest>
void __dbg(const char* names, const T& val, const Rest&... rest) {
    while (*names == ' ') ++names; // skip leading space after a comma, e.g. "x, y" -> "y"
    const char* comma = strchr(names, ',');
    cerr << " " << string(names, comma ? comma - names : strlen(names)) << " = ";
    __print(val);
    cerr << " |";
    __dbg(comma ? comma + 1 : "", rest...);
}

#define dg(...) cerr << "[" << __LINE__ << "]", __dbg(#__VA_ARGS__, __VA_ARGS__)

