#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int a[N];

bool solve(){
	sort(a + 1, a + n + 1);
	for(int i = 1; i + 1 <= n; i++){
		if(2 * a[i] - 1 >= a[i + 1] and a[i] < a[i + 1]) return true;
	}
	return false;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	puts(solve() ? "YES" : "NO");
	return 0;
}
