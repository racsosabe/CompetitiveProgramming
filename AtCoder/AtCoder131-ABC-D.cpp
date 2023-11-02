#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int a[N];
int b[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d %d", a + i, b + i);
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return b[i] < b[j];
	});
	long long timer = 0;
	bool can = true;
	for(int i : p){
		if(timer + a[i] > b[i]) can = false;
		timer += a[i];
	}
	puts(can ? "Yes" : "No");
	return 0;
}
