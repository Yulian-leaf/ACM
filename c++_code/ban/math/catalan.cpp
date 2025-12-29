// 函数功能: 计算Catalan的第n项
// 函数参数: n为项数
// 返回值:  第n个Catalan数
int Catalan(int n) {
  if (n <= 1)
    return 1;
  int *h = new int[n + 1];     // 保存临时结果
  h[0] = h[1] = 1;             // h(0)和h(1)
  for (int i = 2; i <= n; ++i) // 依次计算h(2),h(3)...h(n)
  {
    h[i] = 0;
    for (int j = 0; j < i;
         j++) // 根据递归式计算 h(i)= h(0)*h(i-1)+h(1)*h(i-2) + ... + h(i-1)h(0)
      h[i] += (h[j] * h[i - 1 - j]);
  }
  int result = h[n]; // 保存结果
  delete[] h;        // 注意释放空间
  return result;
}
