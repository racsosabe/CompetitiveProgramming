#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
string s;
int z[N];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	while(getline(cin, s)){
		n = s.size();
		s += '#';
		int l = 0, r = 0;
		for(int i = 1; i < n; i++){
			z[i] = min(z[i - l], r - i + 1);
			if(z[i] < 0) z[i] = 0;
			while(i + z[i] < n and s[i + z[i]] == s[z[i]]) z[i] += 1;
			if(r < i + z[i] - 1){
				l = i;
				r = i + z[i] - 1;
			}
		}
		int ans = n;
		for(int i = 1; i < n; i++){
			if(z[i] + i == n){
				ans = i;
				break;
			}
		}
		for(int i = 0; i < ans; i++){
			cout << s[i];
		}
		cout << endl;
	}
	return 0;
}
