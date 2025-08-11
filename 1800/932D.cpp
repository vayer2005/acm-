#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
 
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define int long long
using vpi = vector<pair<int, int>>;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
const int mod = 1e9+7;
const int NUM = 1000030;
const int N = 2e5+5;
const double EPS = 1e-9;
const int INF = 1e9 + 13;
 
typedef __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> ordered_set;
 
 
 
vector<int> lp, sieve;
vector<int> pr;
vector<int> power;
vector<int> fact(2e5 + 5, 0);

void initpow(int x)
{
    power.resize(NUM);
    power[0] = 1;
    for (int i = 1; i < NUM; i++)
    {
        power[i] = (power[i - 1] * (x % mod)) % mod;
    }
}
void initFactorial()
{
    fact.resize(NUM);
    fact[0] = 1;
    for (int i = 1; i < NUM; i++)
    {
        fact[i] = (fact[i - 1] * i) % mod;
    }
}

void calc_sieve()
{
    sieve.resize(NUM + 1, 0);
    for (int x = 2; x <= NUM; x++)
    {
        if (sieve[x])
            continue;
        for (int u = x; u <= NUM; u += x)
        {
            sieve[u] = x;
        }
    }
}
void primefactor()
{
    lp.resize(N + 1, 0);
    for (int i = 2; i <= N; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
            lp[i * pr[j]] = pr[j];
    }
}
int binpow(int a, int b)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
int binpow(int a, int b, int mod)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res % mod;
}
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
int lcm(int a, int b)
{
    return ((a / gcd(a, b)) * b);
}
int inversemod(int a, int mod)
{
    return binpow(a, mod - 2, mod);
}
int divmod(int a, int b, int c)
{
    return ((a % c) * inversemod(b, c)) % c;
}
int C(int n, int k)
{
    if (k > n)
        return 0;
    int p1 = (fact[n] * inversemod(fact[k], mod)) % mod;
    int p2 = (1 * inversemod(fact[n - k], mod)) % mod;
    return (p1 * p2) % mod;
}

int ops(int val) {
    int res = 0;
    int v = val;
    while (v % 2 == 0) {
        v /= 2;
        res++;
    }
    return res;
}

void solve() {
    int n, c;
    cin >> n >> c;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> prefe(n,0);
    vector<int> prefo(n,0);
    prefe[0] = (a[0] %2 == 0);
    prefo[0] = (a[0] %2 != 0);
    for (int i = 1; i < n; i++) {
        prefe[i] = prefe[i-1] + (a[i] %2 == 0);
        prefo[i] = prefo[i-1] + (a[i] %2 != 0);
    }

    int tot = 0;
    for (int i = 0; i < n; i++) {
        int curr = (a[i]/2) + 1;
        int mx = 2*c-a[i];
        auto it = upper_bound(a.begin(), a.end(), mx);
        int ind = n-1;
        if (it != a.end()) {
            ind = it - a.begin()-1;
        }
        if (ind >= 0) {
            int excl;
            if (a[i] % 2 == 0) {
                excl = prefe[ind] - prefe[i];
            } else {
                excl = prefo[ind] - prefo[i];
            }

            int delta=((mx - a[i])/2) - excl;
            curr += delta;
        }
        
        tot += curr;
    }

    cout << ((c+1)*(c+2)/2) - tot << endl;
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;cin >> t;
    while (t--) solve();
    
    return 0;
 
}