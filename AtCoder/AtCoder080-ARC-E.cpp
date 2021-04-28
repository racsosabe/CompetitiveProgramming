#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Notice that the first element of the pair for range [l, r] must be on an odd position x,

	  and we want to minimize it. After that, we only need the minimum possible

	  match, which will be on an even position that is greater than x.

	- After taking the matching pair we are left with some independent intervals,

	  so we will use a priority queue to know which pair need to follow.

	- If we use RMQ to get the minimum odd/even position in a range, we have a O(nlogn) solution.

	- Complexity: O(nlogn)

*/

const int N = 200000 + 5;

int n;
int a[N];
int position[N];
int st[2][4 * N];

void build(int id, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[id][pos] = 1e9;
		return;
	}
	int mi = (l + r) / 2;
	build(id, 2 * pos, l, mi);
	build(id, 2 * pos + 1, mi + 1, r);
	st[id][pos] = min(st[id][2 * pos], st[id][2 * pos + 1]);
}

void update(int id, int x, int y, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[id][pos] = y;
		return;
	}
	int mi = (l + r) / 2;
	if(x <= mi) update(id, x, y, 2 * pos, l, mi);
	else update(id, x, y, 2 * pos + 1, mi + 1, r);
	st[id][pos] = min(st[id][2 * pos], st[id][2 * pos + 1]);
}

int query(int id, int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return 1e9;
	if(x <= l and r <= y) return st[id][pos];
	int mi = (l + r) / 2;
	return min(query(id, x, y, 2 * pos, l, mi), query(id, x, y, 2 * pos + 1, mi + 1, r));
}

void solve(){
	typedef pair<int, pair<int, int> > node;
	priority_queue<node, vector<node>, greater<node> > Q;
	Q.emplace(make_pair(query(1, 1, n), make_pair(1, n)));
	while(!Q.empty()){
		int cur = Q.top().first;
		pair<int, int> pos = Q.top().second;
		Q.pop();
		int l = pos.first;
		int r = pos.second;
		int x = position[cur];
		int y = position[query((l & 1) ^ 1, x, r)];
		printf("%d %d ", a[x], a[y]);
		if(x != l){
			Q.emplace(make_pair(query(l & 1, l, x - 1), make_pair(l, x - 1)));
		}
		if(y != r){
			
			Q.emplace(make_pair(query((y + 1) & 1, y + 1, r), make_pair(y + 1, r)));
		}
		if(x + 1 <= y - 1){
			Q.emplace(make_pair(query((x + 1) & 1, x + 1, y - 1), make_pair(x + 1, y - 1)));
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
		position[a[i]] = i;
	}
	for(int i = 0; i < 2; i++) build(i);
	for(int i = 1; i <= n; i++){
		update(i & 1, i, a[i]);
	}
	solve();
	puts("");
	return 0;
}
