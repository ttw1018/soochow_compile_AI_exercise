#include <algorithm>
#include <bits/stdc++.h>
#include <bits/types/cookie_io_functions_t.h>
#include <cstdlib>

using namespace std;

// 方程最小值
double l = 0;

// 方程最大值
double r = 10;

// 给定的精度
double precisous = 0.01;

// 使用的随机数的位数
int bitcnt;

// 最大的随机数的范围
int maxrandom;

// 给定的方程
double f(double x) { return 10 * sin(5 * x) + 7 * abs(x - 5) + 10; }

// 求当前x对应的函数值
double getval(int x) { return l + x * precisous; }

void getbit() {
  int all = (r - l) / precisous;
  maxrandom = all + 1;
  int cnt = 0;
  while (all) {
    cnt++;
    all >>= 1;
  }
}

//  生成随机数
int get_rand() {
  srand(int(time(0)));
  for (int i = 1; i < 20; i++) {
    int a = random() % maxrandom;
  }
  printf("\n");
  return 0;
}

// 选取第一代
vector<double> get_first_gen(int n) {
  vector<double> v;
  for (int i = 1; i <= n; i++) {
    int a = rand() % maxrandom;
    v.push_back(getval(a));
  }
  return v;
}


// 根据当前值获得编码
int getid(double x) {
	return (x - l) / precisous;
}

// 
double cross_possibility = 0.2;

// 交叉
void cross(vector<double> v) {
	int times = 10;

	while (times--) {
		int a = rand() % 100;
		if (a / 100.0 < cross_possibility) {
			int p1 = rand() % v.size();
			int p2 = rand() % v.size();

			// 获得编码
			int id1 = getid(v[p1]);
			int id2 = getid(v[p2]);
			
			// 交叉位，单点交叉
			int bit = rand() % bitcnt;

			int b1 = (id1 >> bit) & 1;
			int b2 = (id2 >> bit) & 1;
			id1 ^= b1 << bit;
			id2 ^= b2 << bit;
			swap(b1, b2);
			id1 ^= b1 << bit;
			id2 ^= b2 << bit;
			
			v[p1] = getval(id1);
			v[p2] = getval(id2);
		}
	}
	
}

double variation_possibility = 0.01;

// 变异
void variation(vector<double> v) {
	int times = 10;

	while (times--) {
		int a = rand() % 100;
		if (a / 100.0 < variation_possibility) {
			int bit = rand() % bitcnt;

			int pos = rand() % v.size();

			int id = getid(v[pos]);

			id = id ^ (1 << bit);

			v[pos] = getval(id);

		}
	}

}

#define pdd pair<double, double>

vector<double> get_next(vector<double> v) {
  vector<pdd> now;
  double sum = 0;
  for (auto i : v) {
    now.push_back({i, f(i)});
    sum += f(i);
  }

  vector<pair<int, int>> pos;

  double tmp = 0;
  for (auto i : now) {
    pair<int, int> cross;
    cross.first = tmp * 1000;
    tmp += i.second / sum;
    cross.second = tmp * 1000;
    pos.push_back(cross);
  }

  vector<double> ans;
  for (int i = 0; i < v.size(); i++) {
    int ran = rand() % 1000;
    for (int i = 0; i < pos.size(); i++) {
      if (pos[i].first <= ran && pos[i].second > ran) {
        ans.push_back(v[i]);
      }
    }
  }


	// 交叉
//	cross(ans);

	// 变异
	variation(ans);

  return ans;
}

int main() {
  getbit();

  // 获取第一代
  vector<double> gen = get_first_gen(10);

  // 迭代次数
  int times = 100;

  while (times--) {
    gen = get_next(gen);
  }
	for (auto i : gen) {
		cout << i << " ";
	}
	cout << endl;

  return 0;
}
