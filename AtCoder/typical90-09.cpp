#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;

int n;
long double ans;
pair<int, int> v[N];
pair<int, int> carry[N];

long long cross(pair<int, int> a, pair<int, int> b){
	return 1ll * a.first * b.second - 1ll * a.second * b.first;
}

bool toLeft(pair<int, int> a, pair<int, int> b){
	return cross(b, a) >= 0;
}

void solve(int idx){
	int pos = 0;
	for(int i = 0; i < n; i++){
		if(i == idx) continue;
		carry[pos++] = make_pair(v[i].first - v[idx].first, v[i].second - v[idx].second);
	}
	sort(carry, carry + n - 1, [&] (pair<int, int> a, pair<int, int> b){
		if((a.first <= 0) ^ (b.first <= 0)) return a.first > b.first;
		return toLeft(b, a);
	});
	int m = n - 1;
	pos = 1;
	for(int i = 0; i < m; i++){
		while(toLeft(carry[pos], carry[i])){
			pos += 1;
			if(pos == m) pos = 0;
		}
		cout << i << " -> " << (pos + m - 1) % m << endl;
		pos += 1;
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d %d", &v[i].first, &v[i].second);
	for(int i = 0; i < n; i++){
		solve(i);
	}
	printf("%.10Lf\n", ans);
	return 0;
}
