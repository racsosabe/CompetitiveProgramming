#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Sorting problem.

	- Just consider that we will have some sets of values that have the same

	  initial a[i], then we obviously will want the mininum to be mantained until

	  we get a different a[i] value for all of them.

	- We can accelerate the process sorting the pairs (a[i], i) decreasingly

	  and updating the sum of heights of the current positions: Each time we have

	  a[p[i]] != a[p[i] + 1], we need to update all the heights to a[p[i] + 1]

	  and add those cells to the current minimum p[i].

	- Complexity: O(nlogn)

*/

const int N = 100000 + 5;

int n;
long long ans[N];
pair<int, int> a[N];

void solve(){
	sort(a + 1, a + n + 1, greater< pair<int, int> >());
	int minimo = n + 1;
	long long suma = 0;
	for(int i = 1; i < n; i++){
		suma += a[i].first;
		minimo = min(minimo, a[i].second);
		if(a[i].first != a[i + 1].first){
			int nxt = a[i + 1].first;
			int dif = a[i].first - nxt;
			ans[minimo] += 1ll * dif * i;
			suma -= 1ll * dif * i;
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i].first);
		a[i].second = i;
	}
	a[n + 1].first = 0;
	a[n + 1].second = n + 1;
	n += 1;
	solve();
	for(int i = 1; i < n; i++){
		printf("%lld\n", ans[i]);
	}
	return 0;
}
