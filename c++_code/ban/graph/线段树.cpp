// 节点数据结构
struct node {
  int l, r;
  int val;
} t[4 * maxn + 2];

// 记录原始数据
int a[maxn + 2];

// 建树
void build(int u, int l, int r) {
  t[u].l = l;
  t[u].r = r;
  if (l == r) {
    t[u].val = a[l];
    return;
  }
  int mid = (l + r) / 2;
  build(u * 2, l, mid);
  build(u * 2 + 1, mid + 1, r);
  t[u].val = t[u * 2].val + t[u * 2 + 1].val;
}
// 单点修改
void modify(int u, int x,
            int y) { // u为节点编号，x为要修改的位置，y为要修改的值
  if (t[u].l == t[u].r) {
    t[u].val = y;
    return;
  }
  int mid = (t[u].l + t[u].r) / 2;
  if (x <= mid)
    modify(u * 2, x, y);
  else
    modify(u * 2 + 1, x, y);
  t[u].val = t[u * 2].val + t[u * 2 + 1].val;
}
// 更新子节点
void pushdown(int u) {
  // 将lazy标记向下传给左右孩子节点
  t[u * 2].lazy += t[u].lazy;
  t[u * 2 + 1].lazy += t[u].lazy;
  // 更新左右孩子节点的值，为lazy标记×孩子节点表示的区间长度，记得减1
  t[u * 2].val += t[u].lazy * (t[u * 2].r - t[u * 2].l + 1);
  t[u * 2 + 1].val += t[u].lazy * (t[u * 2 + 1].r - t[u * 2 + 1].l + 1);
  // 清除该节点的lazy标记，防止重复更新
  t[u].lazy = 0;
}

// 更新父节点
void pushup(int u) { t[u].val = t[u * 2].val + t[u * 2 + 1].val; }

// 区间修改
void modify2(int u, int l, int r, int x) { // x为要求区间修改的值
  // 找到子区间，则不需要向下寻找
  if (l <= t[u].l && t[u].r <= r) {
    t[u].lazy += x;
    t[u].val += x * (t[u].r - t[u].l + 1);
    return;
  }
  // 若区间分布在节点表示的区间两侧，则分别查找左右孩子表示的区间
  int mid = (t[u].l + t[u].r) / 2;
  // 需要查找孩子节点，要将lazy标记向下传递
  pushdown(u);
  if (l <= mid)
    modify2(u * 2, l, r, x);
  if (mid < r)
    modify2(u * 2 + 1, l, r, x);
  // 修改完成后要记得更新父节点的值
  pushup(u);
}
// 区间查询
int query(int u, int L, int R) {
  // 若不在节点表示的区间内，则找不到
  if (t[u].l > R || t[u].r < L)
    return 0;
  // 若节点正好是要查询的子区间，则直接返回该节点的值
  if (t[u].l >= L && t[u].r <= R)
    return t[u].val;
  // 若要查找的区间分布在节点表示的区间两侧，则递归分别查找
  // 记得传递lazy标记，更新孩子节点的值
  pushdown(u);
  return query(u * 2, L, R) + query(u * 2 + 1, L, R);
}
// 更新父节点
void pushup(int u) { t[u].maxv = max(t[u * 2].maxv, t[u * 2 + 1].maxv); }

// 更新子节点
void pushdown(int u) {
  t[u * 2].lazy += t[u].lazy;
  t[u * 2 + 1].lazy += t[u].lazy;
  t[u * 2].maxv += t[u].lazy;
  t[u * 2 + 1].maxv += t[u].lazy;
  t[u].lazy = 0;
}

// 区间修改
void modify(int u, int l, int r, int x) {
  if (t[u].l > r || t[u].r < l)
    return;
  if (t[u].l >= l && t[u].r <= r) {
    t[u].lazy += x;
    t[u].maxv += x;
    return;
  }
  int mid = (t[u].l + t[u].r) / 2;
  pushdown(u);
  modify(u * 2, l, r, x);
  modify(u * 2 + 1, l, r, x);
  pushup(u);
}

// 区间查询
int query(int u, int l, int r) {
  if (t[u].l > r || t[u].r < l)
    return -1e9;
  if (t[u].l >= l && t[u].r <= r) {
    return t[u].maxv;
  }
  int mid = (t[u].l + t[u].r) / 2;
  pushdown(u);
  int ans = -0x3f3f3f;
  ans = max(ans, query(u * 2, l, r));
  ans = max(ans, query(u * 2 + 1, l, r));
  pushup(u);
  return ans;
}
