#include<bits/stdc++.h>
using namespace::std;

int n;
vector< pair<int, int> > points;

bool can(int x, vector< pair<int, int> > v){
	if(v.empty()) return true;
	int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
	for(auto e : v){
		minX = min(minX, e.first);
		maxX = max(maxX, e.first);
		minY = min(minY, e.second);
		maxY = max(maxY, e.second);
	}
	vector< pair<int, int> > Lx = get(v, minX, x);
	vector< pair<int, int> > Ly = get(v, minX, x);
	vector< pair<int, int> > Lx = get(v, minX, x);
	vector< pair<int, int> > Lx = get(v, minX, x);
}

int solve(){
	int lo = 0, hi = 50000;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(not can(mi, points)) lo = mi + 1;
		else hi = mi;
	}
	return lo;
}

int main(){
	scanf("%d", &n);
	points.resize(n);
	for(int i = 0; i < n; i++){
		scanf("%d %d", &points[i].first, &points[i].second);
	}
	printf("%d\n", solve());
	return 0;
}
