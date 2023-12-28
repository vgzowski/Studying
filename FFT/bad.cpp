// includes
#include <bits/stdc++.h>
using namespace std;

// macros
#define pb emplace_back
#define mk make_pair
#define FOR(i, a, b) for(int i=(a);i<(b);++i)
#define rep(i, n) FOR(i, 0, n)
#define rrep(i, n) for(int i=((int)(n)-1);i>=0;i--)
#define irep(itr, st) for(auto itr = (st).begin(); itr != (st).end(); ++itr)
#define irrep(itr, st) for(auto itr = (st).rbegin(); itr != (st).rend(); ++itr)
#define whole(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define UNIQUE(v) v.erase(unique(v.begin(), v.end()), v.end())
#define bit(n) (1LL<<(n))
// functions
template <class T>bool chmax(T &a, const T &b){if(a < b){a = b; return 1;} return 0;}
template <class T>bool chmin(T &a, const T &b){if(a > b){a = b; return 1;} return 0;}
template <typename T> istream &operator>>(istream &is, vector<T> &vec){for(auto &v: vec)is >> v; return is;}
template <typename T> ostream &operator<<(ostream &os, const vector<T>& vec){for(int i = 0; i < vec.size(); i++){ os << vec[i]; if(i + 1 != vec.size())os << " ";} return os;}
template <typename T> ostream &operator<<(ostream &os, const set<T>& st){for(auto itr = st.begin(); itr != st.end(); ++itr){ os << *itr; auto titr = itr; if(++titr != st.end())os << " ";} return os;}
template <typename T> ostream &operator<<(ostream &os, const unordered_set<T>& st){for(auto itr = st.begin(); itr != st.end(); ++itr){ os << *itr; auto titr = itr; if(++titr != st.end())os << " ";} return os;}
template <typename T> ostream &operator<<(ostream &os, const multiset<T>& st){for(auto itr = st.begin(); itr != st.end(); ++itr){ os << *itr; auto titr = itr; if(++titr != st.end())os << " ";} return os;}
template <typename T> ostream &operator<<(ostream &os, const unordered_multiset<T>& st){for(auto itr = st.begin(); itr != st.end(); ++itr){ os << *itr; auto titr = itr; if(++titr != st.end())os << " ";} return os;}
template <typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &p){os << "(" << p.first << ", " << p.second << ")"; return os;}
template <typename T1, typename T2> ostream &operator<<(ostream &os, const map<T1, T2> &mp){for(auto itr = mp.begin(); itr != mp.end(); ++itr){ os << "(" << itr->first << ", " << itr->second << ")"; auto titr = itr; if(++titr != mp.end())os << " "; } return os;}
template <typename T1, typename T2> ostream &operator<<(ostream &os, const unordered_map<T1, T2> &mp){for(auto itr = mp.begin(); itr != mp.end(); ++itr){ os << "(" << itr->first << ", " << itr->second << ")"; auto titr = itr; if(++titr != mp.end())os << " "; } return os;}
//  types
using ll = long long int;
using P = pair<int, int>;
// constants
const int inf = 1e9;
const ll linf = 1LL << 50;
const double EPS = 1e-10;
const int mod = 1000000007;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};
// io
struct fast_io{
  fast_io(){ios_base::sync_with_stdio(false); cin.tie(nullptr); cout << fixed << setprecision(20);}
} fast_io_;

template<typename T>
T extgcd(T a, T b, T &x, T &y){ 
  T d = a;
  if(b != 0){
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  }else{
    x = 1, y = 0;
  }
  return d;
}

template <typename T>
T modinv(T a, T m){
  long long x = 0, y = 0;
  extgcd<long long>(a, m, x, y);
  x %= m;
  if(x < 0)x += m;
  return x;
}

template <typename T>
long long garner(vector<T> b, vector<T> m, T MOD){
  m.emplace_back(MOD);
  vector<long long> coef(m.size(), 1);
  vector<long long> consts(m.size(), 0);
  for(int i = 0; i < b.size(); i++){
    long long t = ((b[i] - consts[i]) % m[i]) * modinv<long long>(coef[i], m[i]) % m[i];
    if(t < 0)t += m[i];
    for(int j = i + 1; j < m.size(); j++){
      consts[j] = (consts[j] + t * coef[j] % m[j]) % m[j];
      coef[j] = coef[j] * m[i] % m[j];
    }
  }
  return consts.back();
}

template <typename T>
T power(T a, T n, T mod) {
  T res = 1;
  T tmp = n;
  T curr = a;
  while(tmp){
    if(tmp % 2 == 1){
      res = (T)(res * curr % mod);
    }
    curr = (T)(curr * curr % mod);
    tmp >>= 1;
  }

  return res;
}

template <int MOD, int g>
struct NTT{
  int get_mod(){
    return MOD;
  }
  void _ntt(vector<long long> &f, bool inv=false){
    int n = f.size(), mask = n - 1;
    int h = power<long long>(g, (MOD - 1) / n, MOD);
    if(inv)h = modinv(h, MOD);
    vector<long long> tmp(n);
    for(int i = n >> 1; i >= 1; i >>= 1){
      long long zeta = power<long long>(h, i, MOD);
      long long w = 1;
      for(int j = 0; j < n; j += i){
        for(int k = 0; k < i; k++){
          tmp[j+k] = (f[((j<<1)&mask)+k] + w * f[(((j<<1)+i)&mask)+k] % MOD) % MOD;
        }
        w = w * zeta % MOD;
      }
      swap(f, tmp);
    }
  }
  void ntt(vector<long long> &f){
    _ntt(f, false);
  }
  void intt(vector<long long> &f){
    _ntt(f, true);
    int n = f.size();
    int ni = modinv(n, MOD);
    for(int i = 0; i < n; i++)f[i] = f[i] * ni % MOD;
  }
  vector<long long> convolution(vector<long long> f, vector<long long> h){
    int n = 1;
    while(n < int(f.size() + h.size()))n *= 2;
    f.resize(n, 0); h.resize(n, 0);
    ntt(f);
    ntt(h);
    for(int i = 0; i < n; i++)f[i] = f[i] * h[i] % MOD;
    intt(f);
    return f;
  }
};

using NTT1 = NTT<167772161, 3>;
using NTT2 = NTT<469762049, 3>;
using NTT3 = NTT<1224736769, 3>;

vector<long long> arbitrary_mod_convolution(vector<long long> f, vector<long long> g, long long MOD){
  for(size_t i = 0; i < f.size(); i++)f[i] %= MOD;
  for(size_t i = 0; i < g.size(); i++)g[i] %= MOD;
  NTT1 ntt1;
  NTT2 ntt2;
  NTT3 ntt3;
  auto x1 = ntt1.convolution(f, g);
  auto x2 = ntt2.convolution(f, g);
  auto x3 = ntt3.convolution(f, g);

  vector<long long> res(x1.size());
  vector<long long> b(3), m(3);
  m[0] = ntt1.get_mod();
  m[1] = ntt2.get_mod();
  m[2] = ntt3.get_mod();
  for(size_t i = 0; i < x1.size(); i++){
    b[0] = x1[i];
    b[1] = x2[i];
    b[2] = x3[i];
    res[i] = garner<long long>(b, m, MOD);
  }
  return res;
}


int main(int argc, char const* argv[])
{
  int n, m; cin >> n >> m;
  vector<ll> a(n), b(m); cin >> a >> b;
  auto res = arbitrary_mod_convolution(a, b, mod);
  res.resize(n + m - 1, 0);
  cout << res << endl;
  return 0;
}
