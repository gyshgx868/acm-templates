namespace HeavyLightDecomposition {
int n, q;
const int N = 100005;
struct Edge {
    int to, next;
} E[N * 2];
int head[N], tot;
int top[N];      // 表示v所在的重链的顶端节点
int fa[N];       // 父亲节点
int deep[N];     // 深度
int num[N];      // 表示以v为根的子树的节点数
int p[N];        // 表示v对应的位置
int fp[N];       // fp和p数组相反
int son[N];      // 重儿子
int pos;

void init() {
    tot = 0;
    pos = 1;
    deep[1] = num[0] = 0;
    memset(head, -1, sizeof(head));
    memset(son, -1, sizeof(son));
}

void addEdge(int u, int v) {
    E[tot].to = v;
    E[tot].next = head[u];
    head[u] = tot++;
}

void dfs1(int u, int pre, int d) {
    deep[u] = d;
    fa[u] = pre;
    num[u] = 1;
    for (int i = head[u]; i != -1; i = E[i].next) {
        int v = E[i].to;
        if (v != pre) {
            dfs1(v, u, d + 1);
            num[u] += num[v];
            if (son[u] == -1 || num[v] > num[son[u]]) {
                son[u] = v;
            }
        }
    }
}

void dfs2(int u, int sp) {
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if (son[u] == -1) {
        return;
    }
    dfs2(son[u], sp);
    for (int i = head[u]; i != -1; i = E[i].next) {
        int v = E[i].to;
        if (v != son[u] && v != fa[u]) {
            dfs2(v, v);
        }
    }
}

#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int seg[N << 2];
void pushUp(int rt) {
    seg[rt] = seg[rt << 1] ^ seg[rt << 1 | 1];
}

void build(int l, int r, int rt = 1) {
    if (l == r) {
        seg[rt] = 0;
        return;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    pushUp(rt);
}

void update(int L, int c, int l, int r, int rt = 1) {
    if (L == l && l == r) {
        seg[rt] = c;
        return;
    }
    int m = (l + r) >> 1;
    if (L <= m) {
        update(L, c, lson);
    } else {
        update(L, c, rson);
    }
    pushUp(rt);
    return;
}

int query(int L, int R, int l, int r, int rt = 1) {
    if (L <= l && r <= R) {
        return seg[rt];
    }
    int ret = 0;
    int m = (l + r) >> 1;
    if (L <= m) {
        ret = ret ^ query(L, R, lson);
    }
    if (m < R) {
        ret = ret ^ query(L, R, rson);
    }
    return ret;
}

int find(int u, int v) {
    int tmp = 0;
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) {
            swap(u, v);
        }
        tmp = tmp ^ query(p[top[u]], p[u], 1, n);
        u = fa[top[u]];
    }
    if (deep[u] > deep[v]) {
        swap(u, v);
    }
    tmp = tmp ^ query(p[u], p[v], 1, n);
    return tmp;
}

} // namespace HeavyLightDecomposition

int main() {
    int t;
    scanf("%d", &t);
    using namespace HeavyLightDecomposition;
    while (t--) {
        scanf("%d%d", &n, &q);
        init();
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        dfs1(1, 0, 0);
        dfs2(1, 1);
        build(1, n);
        for (int i = 1; i <= n; i++) {
            int tmp;
            scanf("%d", &tmp);
            update(p[i], tmp + 1, 1, n);
        }
        while (q--) {
            int opt, x, y;
            scanf("%d%d%d", &opt, &x, &y);
            if (opt == 0) {
                y++;
                update(p[x], y, 1, n);
            } else {
                int ans = find(x, y);
                if (ans == 0) {
                    puts("-1");
                } else {
                    printf("%d\n", ans - 1);
                }
            }
        }
    }
    return 0;
}