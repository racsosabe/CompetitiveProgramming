#include<cstdio>
#include<stack>
#include<utility>
#include<climits>
#include<iostream>
using namespace::std;

const int N = 200000 + 5;
const int inf = 1e9;

struct MaxStack{
	stack< pair< pair<int, int>, pair<int, int> > > S;
	void push(pair<int, int> x){
		if(S.empty()) S.emplace(make_pair(x, x));
		else S.emplace(make_pair(x, max(S.top().second, x)));
	}

	void pop(){
		S.pop();
	}

	pair<int, int> top(){
		return S.top().first;
	}

	bool empty(){
		return S.empty();
	}

	pair<int, int> getMax(){
		return S.empty() ? make_pair(INT_MIN, INT_MIN) : S.top().second;
	}
};

struct MaxQueue{
	MaxStack in, out;

	void push(pair<int, int> x){
		in.push(x);
	}

	void pop(){
		if(out.empty()){
			while(!in.empty()){
				pair<int, int> x = in.top();
				out.push(x);
				in.pop();
			}
		}
		out.pop();
	}

	pair<int, int> getMax(){
		return max(in.getMax(), out.getMax());
	}
};

int n;
int k;
int m;
int a[N];
int prefix[N];

void solve(){
	int ans = -inf;
	int l = -1, r = -1;
	for(int i = 1; i <= m; i++){
		prefix[i] = prefix[i - 1] + a[i];
	}
	MaxQueue Q;
	Q.push(make_pair(prefix[m], -m));
	for(int i = m - 1; i >= 0; i--){
		pair<int, int> best = Q.getMax();
		int cur = best.first - prefix[i];
		int len = -best.second - i;
		if(make_pair(ans, -(r - l + 1)) <= make_pair(cur, -len)){
			ans = cur;
			l = i + 1;
			r = -best.second;
		}
		Q.push(make_pair(prefix[i], -i));
		if(i + k <= m) Q.pop();
	}
	if(l > n) l -= n;
	if(r > n) r -= n;
	printf("%d %d %d\n", ans, l, r);
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &k);
		m = n << 1;
		for(int i = 1; i <= n; i++){
			scanf("%d", a + i);
			a[i + n] = a[i];
		}
		solve();
	}
	return 0;
}
