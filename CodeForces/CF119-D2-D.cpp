#include<bits/stdc++.h>
using namespace::std;

vector<int> get_z(string text, string pat) {
	string s = pat + char(0) + text;
	vector<int> Z(s.size(), 0);
	int l = 0, r = 0;
	for(int i = 1; i < s.size(); i++) {
		Z[i] = min(Z[i - l], r - i + 1);
		if(Z[i] < 0) Z[i] = 0;
		while(i + Z[i] < s.size() and s[Z[i]] == s[i + Z[i]]) Z[i] += 1;
		if(i + Z[i] - 1 > r) {
			l = i;
			r = i + Z[i] - 1;
		}
	}
	return vector<int>(Z.begin() + pat.size() + 1, Z.end());
}

void solve(string &a, string &b) {
	const int n = a.size();
	string rb = b;
	reverse(rb.begin(), rb.end());
	string ra = a;
	reverse(ra.begin(), ra.end());
	vector<int> z_a_rb = get_z(a, rb);
	vector<int> z_a_b = get_z(a, b);
	vector<int> z_b_ra = get_z(b, ra);
	for(int i = z_a_rb[0] - 1; i >= 0; i--) {
		if(i + 1 == n) continue;
		int l1 = min(z_a_b[i + 1], n - i - 1);
		int l2 = min(z_b_ra[l1], n - i - 1);
		if(l1 + l2 >= n - i - 1) {
			for(int j = 0; j <= l1; j++) {
				if(j + z_b_ra[j] >= n - i - 1) {
					cout << i << " " << i + j + 1 << endl;
					break;
				}
			}
			return;
		}
	}
	cout << -1 << " " << -1 << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	string a, b;
	getline(cin, a);
	getline(cin, b);
	if(a.size() != b.size()) {
		cout << -1 << " " << -1 << endl;
		return 0;
	}
	solve(a, b);
	return 0;
}
