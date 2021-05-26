#include<bits/stdc++.h>
using namespace::std;

const int N = 50 + 5;

int n;
int a[N];
int b[N];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	for(int i = 0; i < n; i++) scanf("%d", b + i);
	vector<int> p(n);
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&] (int i, int j){
		if((a[i] ^ b[i]) == (a[j] ^ b[j])) return i < j;
		return (a[i] ^ b[i]) > (a[j] ^ b[j]);
	});
	int ans = 0;
	for(int i = 0; i < n; i++){
		int cur = a[p[i]] ^ b[p[i]];
		for(int j = 0; j < i; j++){
			cur = min(cur, a[p[i]] ^ b[p[j]]);
		}
		ans += cur;
	}
	printf("%d\n", ans);
	for(int i = 0; i < n; i++){
		printf("%d%c", p[i] + 1, " \n"[i + 1 == n]);
	}
	return 0;
}
