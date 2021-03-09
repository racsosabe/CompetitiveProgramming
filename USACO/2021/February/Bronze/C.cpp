#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;
const string CCW = "NwSE";

int n;
char s[N];
char a[N];
vector< pair<int, int> > dir;

bool check(){
	vector< pair<int, int> > points;
	points.emplace_back(make_pair(0, 0));
	int x = 0, y = 0;
	for(int i = 0; i + 1 < dir.size(); i++){
		x += dir[i].first;
		y += dir[i].second;
		points.emplace_back(make_pair(x, y));
	}
	long long area = 0;
	for(int i = 0; i < points.size(); i++){
		int j = i + 1 < points.size() ? i + 1 : 0;
		area += points[i].first * points[j].second - points[i].second * points[j].first;
	}
	return area > 0;
}

bool solve(){
	dir.clear();
	int shift = 0;
	for(int i = 1; i < n; i++){
		if(s[i] != s[i - 1]) shift = i;
	}
	for(int i = 0; i < n; i++){
		int pos = (i + shift) % n;
		a[i] = s[pos];
	}
	int L = 0, R = 0;
	while(L < n){
		while(R < n and s[L] == s[R]){
			R += 1;
		}
		int dis = R - L;
		if(s[L] == 'N'){
			dir.emplace_back(make_pair(0, dis));
		}
		else if(s[L] == 'S'){
			dir.emplace_back(make_pair(0, -dis));
		}
		else if(s[L] == 'E'){	
			dir.emplace_back(make_pair(dis, 0));
		}
		else{
			dir.emplace_back(make_pair(-dis, 0));
		}
		L = R;
	}
	return check();
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%s", s);
		n = strlen(s);
		puts(solve() ? "CCW" : "CW");
	}
	return 0;
}
