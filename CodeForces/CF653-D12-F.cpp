#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;
const int LOG = 20;

int n;
int h[N];
char s[N];
int ST[N][LOG];
vector<int> G[N];

vector<int> suffix_array(){
	s[n++] = 0;
	vector<int> a(n);
	iota(a.begin(), a.end(), 0);
	sort(a.begin(), a.end(), [&] (int i, int j){
		return s[i] < s[j];
	});
	vector<int> m(n);
	m[a[0]] = 0;
	for(int i = 1; i < n; i++){
		m[a[i]] = m[a[i - 1]] + (s[a[i - 1]] != s[a[i]]);
	}
	int len = 1;
	vector<int> nm(n);
	vector<int> sbs(n);
	vector<int> head(n);
	while(len < n){
		for(int i = 0; i < n; i++){
			sbs[i] = (a[i] - len + n) % n;
		}
		for(int i = n - 1; i >= 0; i--){
			head[m[a[i]]] = i;
		}
		for(int i = 0; i < n; i++){
			int x = sbs[i];
			a[head[m[x]]++] = x;
		}
		nm[a[0]] = 0;
		for(int i = 1; i < n; i++){
			if(m[a[i]] != m[a[i - 1]]){
				nm[a[i]] = nm[a[i - 1]] + 1;
			}
			else{
				int pre = m[(a[i - 1] + len) % n];
				int cur = m[(a[i] + len) % n];
				nm[a[i]] = nm[a[i - 1]] + (pre != cur);
			}
		}
		swap(m, nm);
		len <<= 1;

	}
	return a;
}

vector<int> lcp_array(vector<int> &a){
	vector<int> rank(n);
	for(int i = 0; i < n; i++){
		rank[a[i]] = i;
	}
	int k = 0;
	vector<int> lcp(n - 1);
	for(int i = 0; i < n; i++){
		if(rank[i] + 1 == n){
			k = 0;
			continue;
		}
		int j = a[rank[i] + 1];
		while(i + k < n and j + k < n and s[i + k] == s[j + k]) k += 1;
		lcp[rank[i]] = k;
		if(k) k -= 1;
	}
	return lcp;
}

void computeLCA(int u, int p){
	ST[u][0] = p;
	for(int d = 1; 1 << d <= h[u]; d++){
		ST[u][d] = ST[p][0];
		p = ST[p][d];
	}
}

void DFS(int u, int p = -1){
	computeLCA(u, p);
	for(int v : G[u]){
		h[v] = h[u] + 1;
		DFS(v, u);
	}
}

void preprocess(){
	stack<int> S;
	G[n].emplace_back(n - 1);
	for(int i = n - 2; i >= 0; i--){
		int par = n;
		if(s[i] == '('){
			if(not S.empty()){
				par = S.top() + 1;
				S.pop();
			}
		}
		else{
			S.emplace(i);
		}
		G[par].emplace_back(i);
	}
	DFS(n);
}

int getBalanced(int pos, int l){
	if(s[pos] == ')') return 0;
	for(int i = LOG - 1; i >= 0; i--){
		if((1 << i) <= h[pos] and ST[pos][i] - 1 < l){
			pos = ST[pos][i];
		}
	}
	if(ST[pos][0] - 1 >= l) return h[pos] - 1;
	return h[ST[pos][0]];
}

long long solve(){
	vector<int> a = suffix_array();
	vector<int> lcp = lcp_array(a);
	preprocess();
	int extra = 0;
	long long ans = 0;
	for(int i = 0; i < a.size(); i++){
		ans += getBalanced(a[i], a[i] + extra);
		if(i + 1 < n) extra = lcp[i];
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	printf("%lld\n", solve());
	return 0;
}
