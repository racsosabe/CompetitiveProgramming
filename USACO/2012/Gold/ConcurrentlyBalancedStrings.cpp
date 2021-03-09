#include<bits/stdc++.h>
using namespace::std;

void setIO(string name, bool input, bool output){
	string inputname = name + ".in";
	string outputname = name + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

const int N = 50000 + 5;
const int M = 100000 + 10;
const int K = 10 + 5;

int n;
int k;
int a[N];
char s[K][N];
int ac[K][N];
int ft[K][M];
vector<int> pos[N];
map< vector<int>, int> id;

void compress(){
	int len = 0;
	set< vector<int> > S;
	for(int i = 0; i <= n; i++){
		vector<int> cur(k);
		for(int j = 0; j < k; j++) cur[j] = ac[j][i];
		S.emplace(cur);
	}
	for(auto x : S){
		id[x] = len++;
	}
	for(int i = 0; i <= n; i++){
		vector<int> cur(k);
		for(int j = 0; j < k; j++) cur[j] = ac[j][i];
		a[i] = id[cur];
		pos[a[i]].emplace_back(i);
	}
}

void update(int id, int pos, int val){
	pos++;
	pos += N;
	while(pos < M){
		ft[id][pos] = max(ft[id][pos], val);
		pos += (-pos) & pos;
	}
}

int getMax(int id, int pos){
	pos++;
	pos += N;
	int res = 0;
	while(pos > 0){
		res = max(res, ft[id][pos]);
		pos &= pos - 1;
	}
	return res;
}

int query(int id, int l, int r){
	if(l > r) return 0;
	int lo = 0, hi = pos[id].size() - 1;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(pos[id][mi] < l) lo = mi + 1;
		else hi = mi;
	}
	if(pos[id][lo] < l or pos[id][lo] > r) return 0;
	int lower = lo;
	hi = pos[id].size() - 1;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(pos[id][mi] <= r) lo = mi;
		else hi = mi - 1;
	}
	return lo - lower + 1;
}

int solve(){
	for(int j = 0; j < k; j++){
		for(int i = 1; i <= n; i++){
			ac[j][i] = ac[j][i - 1] + (s[j][i] == '(' ? 1 : -1);
		}
	}
	compress();
	int ans = 0;
	for(int i = 1; i <= n; i++){
		int limit = 0;
		for(int j = 0; j < k; j++){
			limit = max(limit, getMax(j, ac[j][i] - 1));
		}
		ans += query(a[i], limit, i - 1);
		for(int j = 0; j < k; j++){
			update(j, ac[j][i], i);
		}
	}
	return ans;
}

int main(){
	setIO("cbs", 1, 1);
	scanf("%d %d", &k, &n);
	for(int i = 0; i < k; i++){
		scanf("%s", s[i] + 1);
	}
	printf("%d\n", solve());
	return 0;
}
