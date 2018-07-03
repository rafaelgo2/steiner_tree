#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;

#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)

const int MAXN = 100;
const int MAXK = 10;
const int INF = 99999;

#define SUBSETS(x) (1 << x)

typedef pair<int, int> edge;
typedef vector<edge> ve;

typedef vector<int> vi;

int n, m, k;
ve g[MAXN+MAXK];

bool is_subset(bitset<MAXK> l, bitset<MAXK> r){
	return (l != r) && ((l&r) == l);
}

int first_set(bitset<MAXK> s){
	for (int i = 0; i < MAXK; i++) if (s[i]) return i;
	return -1;
}

int last_set(bitset<MAXK> s){
	for (int i = MAXK-1; i >= 0; i--) if (s[i]) return i;
	return -1;
}

bitset<MAXK> set_minus(bitset<MAXK> l, bitset<MAXK> r){
	r.flip();
	return l&r;
}

void subsets(bitset<MAXK> s, int i, vector<bitset<MAXK>> &ans){
	int l = last_set(s);
	if (l == -1) return;
	//cout << l << "vs" << i << endl;
	if (l < i){
		if (s.count() == 0) return;
		ans.pb(s);
		return;
	}
	while (i <= l && !s[i])
		i++;
	subsets(s, i+1, ans);
	if (i <= l){
		s[i] = false;
		subsets(s, i+1, ans);
	}
}

vector<bitset<MAXK>> subsets(bitset<MAXK> s){
	vector<bitset<MAXK>> ans;
	subsets(s, 0, ans);
	return ans;
}

int dist(int o, int d){
	set<pair<int, int>> h;
	static bool visited[MAXN+MAXK];
	memset(visited, false, sizeof visited);

	h.insert(mp(0, o));
	while (!h.empty()){
		auto p = *h.begin();
		h.erase(h.begin());
		int w = p.first, v = p.second;
		if (v == d){
			//cout << o << "->" << d << ": " << w << endl;
			return w;
		}
		if (visited[v]) continue;
		visited[v] = true;
		for (auto n : g[v]){
			int inc = n.first;
			int u = n.second;
			if (visited[u]) continue;
			h.insert(mp(w+inc, u));
		}
	}
	return INF;
}

int MEMO[SUBSETS(MAXK)][MAXN];
int T(bitset<MAXK> D, int v){
	int L = D.to_ulong();
	int R = v;
	if (MEMO[L][R] == -1){
		if (D.count() == 1){
			int t = first_set(D);
			return dist(n+t, v);
		}
		int ans = INF;
		for (int u = 0; u < n; u++){
			for (bitset<MAXK> D_ : subsets(D)){
				if (!is_subset(D_, D)) continue;
				ans = min(ans, 
						T(D_, u) + T(set_minus(D, D_), u) + dist(v, u)
						);
			}
		}
		MEMO[L][R] = ans;
	}
	return MEMO[L][R];
}

int main(){ _
	memset(MEMO, -1, sizeof MEMO);
	/*
	n: number of vertices
	m: number of edges
	k: size of terminals set
	*/
	cin >> n >> m >> k;
	cout << n << "~" << m << "~" << k << endl;
	for (int i = 0; i < n; i++) g[i].clear();
	int u, v, w;
	for (int i = 0; i < m; i++){
		cin >> u >> v >> w;
		g[u].pb(mp(w, v));
		g[v].pb(mp(w, u));
	}
	bitset<MAXK> t;
	for (int i = 0; i < k; i++){
		cin >> u;
		auto tmp = t;
		t[i] = true;
		g[n+i].pb(mp(1, u));
		g[u].pb(mp(1, n+i));
		cout << "~" << u << endl;
	}
	//cout << "~" << t << endl;
	//for (auto t_ : subsets(t))
	//	cout << '\t' << t_ << endl;
	//cout << dist(0, 5) << endl;
	int ans = INF;
	for (int i = 0; i < n; i++)
		ans = min(ans, T(t, i));
	cout << ans-k << endl;
	/*
	in g,
	i < n is the i-th vertex of the graph,
	i > n is the (i-n)-th artificial vertex, or a terminal
	*/

	return 0;
	/*
	bitset<MAXK> s[SUBSETS(MAXK)];
	int counter[SUBSETS(MAXK)];
	memset(counter, 0, sizeof counter);
	for (int i = 0; i < SUBSETS(k); i++) s[i] = i;
	for (int i = 0; i < SUBSETS(k); i++){
		if (s[i].count() <= 1) counter[i] = i;
	}
	for (int i = 0; i < SUBSETS(k); i++){
		if (s[i].count() <= 1) continue;
		counter[i] = 0;
		int parityI = s[i].count()%2;
		for (int j = 0; j < i; j++){
			if ((s[i]&s[j]) != s[j]) continue;
			int parityJ = s[j].count();
			counter[i] += (
				(parityJ == parityI)?
					-counter[j]:
					+counter[j]
			);
		}
		cout << s[i] << "~" << counter[i] << endl;
	}
	*/
}
