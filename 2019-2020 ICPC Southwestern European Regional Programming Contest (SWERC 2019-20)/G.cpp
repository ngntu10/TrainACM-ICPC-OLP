#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e5 + 10;

int R[203][maxN];

int find_root(int mask, int u) {
    if (R[mask][u] == u) return u;
    return R[mask][u] = find_root(mask, R[mask][u]);
}

void Del(int mask, int u) {
    int v = find_root(mask, u + 1);
    R[mask][u] = v;
}
int has[230][230];
int link[230];
int ok[maxN];
void sol() {
    int S, L, N;
    cin >> S >> L >> N;
    vector<string> name(S);
    for (int i = 0; i < S; i++) cin >> name[i];
    sort(name.begin(), name.end());
    name.resize(unique(name.begin(), name.end()) - name.begin());
    S = (int)name.size();
    for (int i = 0; i < L; i++) {
        string s, t;
        cin >> s >> t;
        int u = lower_bound(name.begin(), name.end(), s) - name.begin();
        int v = lower_bound(name.begin(), name.end(), t) - name.begin();
        if (u != v) {
            has[u][v] = 1;
            has[v][u] = 1;
        }
    }
    vector<int> listCheck(N);
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        int u = lower_bound(name.begin(), name.end(), s) - name.begin();
        listCheck[i] = u;
        ok[i] = 1;
    }
    for (int i = 0; i < S; i++) {
        for (int j = 0; j <= N; j++) R[i][j] = j;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < S; j++) {
            while (true) {
                while (link[j] < N && !ok[link[j]]) {
                    Del(j, link[j]);
                    link[j] = find_root(j, link[j]);
                }
                if (link[j] < N && has[j][listCheck[link[j]]]) {
                    Del(j, link[j]);
                    link[j] = find_root(j, link[j]);
                }
                else break;
            }
            int u = link[j];
            if (u < N && listCheck[u] == j) {
                cout << name[j] << ' ';
                Del(j, u);
                link[j] = find_root(j, link[j]);
                ok[u] = 0;
                break;
            }
        }
    }
}

void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
//    cout << '\n';
//    long long mod = 1LL << 40;
//	long long tmp = 1611516670;
//	for (int i = 0; i < 1000; ++i) {
//	    cout << i << ": " << tmp % 2LL << ": ";
//	    cout << tmp / (1 << 20) << ": ";
//	    cout << tmp;
//	    tmp = tmp + tmp / (1 << 20) + 12345;
//	    tmp %= mod;
//	    cout << '\n';
//	}

}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
