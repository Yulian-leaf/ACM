#include <bits/stdc++.h>
using namespace std;
#define Endl "\n"
#define INF 0x3f3f3f3f
#define PI 3.14159265358979323846 // 20f
const int MOD = 998244353;
// const int MOD = 1e9 + 7;
typedef long long ll;
typedef unsigned long long ull;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
#define int ll

// Six-hump camel back function
double six_hump_camel_back(const vector<double> &x) {
  double x1 = x[0], x2 = x[1];
  return (4 - 2.1 * x1 * x1 + pow(x1, 4) / 3) * x1 * x1 + x1 * x2 +
         (-4 + 4 * x2 * x2) * x2 * x2;
}

void work() {
  const int D = 2;                     // 维度
  const double F = 0.5;                // 缩放因子
  const double CR = 0.9;               // 交叉概率
  const vector<double> LOW = {-3, -2}; // 下界
  const vector<double> UP = {3, 2};    // 上界
  const int PS = 30;                   // 种群大小
  const double MaxFEs = 5E3;           // 最大函数评估次数

  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<double> dist(0.0, 1.0);

  struct Individual {
    vector<double> x(2);
    double fitness{0.0};

    // Individual() : x, fitness(0.0) {}

    void calculate_fitness() { fitness = six_hump_camel_back(x); }
  };

  // 初始化种群
  vector<Individual> pop(PS);
  int FEs = 0;

  for (int i = 0; i < PS; i++) {
    for (int j = 0; j < D; j++) {
      pop[i].x[j] = LOW[j] + (UP[j] - LOW[j]) * dist(gen);
    }
    pop[i].calculate_fitness();
    FEs++;
  }

  // 辅助函数：选择不同的随机索引
  auto select_random_indices = [&](int current_idx, int count) -> vector<int> {
    vector<int> indices;
    for (int i = 0; i < PS; i++) {
      if (i != current_idx) {
        indices.push_back(i);
      }
    }
    shuffle(indices.begin(), indices.end(), gen);
    if (indices.size() > count) {
      indices.resize(count);
    }
    return indices;
  };

  // DE 迭代
  while (FEs <= MaxFEs) {
    for (int i = 0; i < PS; i++) {
      // 选择三个不同的随机个体
      vector<int> random_indices = select_random_indices(i, 3);
      if (random_indices.size() < 3)
        continue;

      int r1 = random_indices[0], r2 = random_indices[1],
          r3 = random_indices[2];

      // 创建试验个体
      Individual trial;
      trial.x = pop[i].x; // 复制当前个体

      // 随机维度
      int j_rand = uniform_int_distribution<int>(0, D - 1)(gen);

      // 变异和交叉
      for (int j = 0; j < D; j++) {
        if (dist(gen) < CR || j == j_rand) {
          trial.x[j] = pop[r1].x[j] + F * (pop[r2].x[j] - pop[r3].x[j]);

          // 边界处理
          trial.x[j] = max(LOW[j], min(UP[j], trial.x[j]));
        }
      }

      // 计算试验个体适应度
      trial.calculate_fitness();
      FEs++;

      // 选择：如果试验个体更好，则替换当前个体
      if (trial.fitness < pop[i].fitness) {
        pop[i] = trial;
      }

      if (FEs >= MaxFEs)
        break;
    }
  }

  // 找到最优个体
  int best_idx = 0;
  for (int i = 1; i < PS; i++) {
    if (pop[i].fitness < pop[best_idx].fitness) {
      best_idx = i;
    }
  }

  // 输出结果
  cout << "Best fitness: " << pop[best_idx].fitness << Endl;
  cout << "Best solution: ";
  for (int i = 0; i < D; i++) {
    cout << "x" << i + 1 << " = " << pop[best_idx].x[i] << " ";
  }
  cout << Endl;
  cout << "Function evaluations: " << FEs << Endl;
}

#undef int
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(6);
  int T = 1;
  // cin >> T;
  while (T--) {
    work();
  }
  return 0;
}