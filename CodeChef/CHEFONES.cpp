#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int a[N];

bool can(vector<long long> v = {}){
	if(v.empty()){
		for(int i = 0; i < n; i++) v.emplace_back(a[i]);
	}
	for(int i = 0; i + 1 < v.size(); i++){
		if(v[i] > v[i + 1]) return false;
		v[i + 1] -= v[i];
		v[i] = 0;
	}
	if(v.back() == 0) return true;
	return false;
}

vector<long long> getV(){
	vector<long long> res(n);
	for(int i = 0; i < n; i++) res[i] = a[i];
	return res;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%d", a + i);
		if(can()){
			puts("YES");
			continue;
		}
		if(n == 1){
			puts("NO");
			continue;
		}
		swap(a[0], a[1]);
		if(can()){
			puts("YES");
			continue;
		}
		swap(a[0], a[1]);
		swap(a[n - 2], a[n - 1]);
		if(can()){
			puts("YES");
			continue;
		}
		swap(a[n - 2], a[n - 1]);
		vector<long long> p(n), s(n);
		vector<long long> b = getV();
		p[0] = b[0];
		for(int i = 1; i < n; i++){
			if(p[i - 1] == -1 or b[i - 1] > b[i]){
				p[i] = -1;
			}
			else{
				b[i] -= b[i - 1];
				b[i - 1] = 0;
				p[i] = b[i];
			}
		}
		b = getV();
		s[n - 1] = b[n - 1];
		for(int i = n - 2; i >= 0; i--){
			if(s[i + 1] == -1 or b[i + 1] > b[i]){
				s[i] = -1;
			}
			else{
				b[i] -= b[i + 1];
				b[i + 1] = 0;
				s[i] = b[i];
			}
		}
		bool found = false;
		for(int i = 1; i + 2 < n and !found; i++){
			vector<long long> c = {p[i - 1], a[i], a[i + 1], s[i + 2]};
			if(p[i - 1] == -1 or s[i + 2] == -1) continue;
			swap(c[1], c[2]);
			if(can(c)){
				puts("YES");
				found = true;
			}
		}
		if(not found) puts("NO");
	}
	return 0;
}
