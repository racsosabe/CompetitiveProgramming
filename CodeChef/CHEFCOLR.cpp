#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int a[N];
int b[N];

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", a + i);
		for(int i = 1; i <= n; i++) scanf("%d", b + i);
		map<int, int> id;
		bool can = true;
		for(int i = 1; i <= n; i++){
			if(id.count(a[i])){
				can &= id[a[i]] == b[i];
			}
			else{
				id[a[i]] = b[i];
			}
		}
		puts(can ? "YES" : "NO");
	}
	return 0;
}
