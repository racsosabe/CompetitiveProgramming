#include<bits/stdc++.h>
using namespace::std;

int n;
int k;
map<string, int> F;
map<string, int> last;

int main(){
	ios_base::sync_with_stdio(false);
	cin >> n >> k;
	cin.ignore();
	for(int i = 1; i <= 3 * n; i++){
		string s;
		getline(cin, s);
		F[s] += 1;
		last[s] = i;
	}
	vector< pair<string, int> > values;
	for(auto e : F) values.emplace_back(e);
	sort(values.begin(), values.end(), [&] (pair<string, int> a, pair<string, int> b){
		if(a.second == b.second) return last[a.first] > last[b.first];
		return a.second > b.second;
	});
	for(int i = 0; i < min(k, (int)values.size()); i++){
		cout << values[i].first << endl;
	}
	return 0;
}
