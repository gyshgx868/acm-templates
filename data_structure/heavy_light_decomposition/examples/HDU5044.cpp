const int MAXN = 100005;
struct Edge {
    int to, next;
} E[MAXN * 2];
int head[MAXN], ecnt;
int top[MAXN];   // top[v] 表示 v 所在的重链的顶端节点
int fa[MAXN];    // 父亲节点
int deep[MAXN];  // 深度
int num[MAXN];   // num[v] 表示以 v 为根的子树的节点数
int p[MAXN];     // p[v] 表示 v 对应的位置
int fp[MAXN];    // fp 和 p 数组相反
int son[MAXN];   // 重儿子
int pos;
ll c[MAXN][2];
ll ansN[MAXN], ansE[MAXN];

void init() {
    memset(c, 0, sizeof(c));
    deep[1] = num[0] = 0;
    ecnt = 0;
    memset(head, -1, sizeof(head));
    pos = 1;   // 使用树状数组, 编号从头1开始
    memset(son, -1, sizeof(son));
}

void addEdge(int u, int v) {
    E[ecnt].to = v;
    E[ecnt].next = head[u];
    head[u] = ecnt++;
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

void add(int i, int val, int type) {
    c[i][type] += val;
}

// type = 0: 增加 u->v 路径上所有点的权值
// type = 1: 增加 u->v 路径上所有边的权值
void change(int u, int v, int val, int type) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) {
            swap(u, v);
        }
        add(p[top[u]], val, type);
        add(p[u] + 1, -val, type);
        u = fa[top[u]];
    }
    if (deep[u] > deep[v]) {
        swap(u, v);
    }
    if (type == 0) {
        add(p[u], val, type);
        add(p[v] + 1, -val, type);
    } else {
        if (u != v) {
            add(p[son[u]], val, type);
            add(p[v] + 1, -val, type);
        }
    }
}

struct Node {
    int u, v;
} e[MAXN];
int posN[MAXN], posE[MAXN];

int main() {
    int t;
    scanf("%d", &t);
    for (int tt = 1; tt <= t; tt++) {
        int n, m;
        scanf("%d%d", &n, &m);
        init();
        for (int i = 1; i < n; i++) {
            scanf("%d%d", &e[i].u, &e[i].v);
            addEdge(e[i].u, e[i].v);
            addEdge(e[i].v, e[i].u);
        }
        dfs1(1, 0, 0);
        dfs2(1, 1);
        for (int i = 1; i < n; i++) {
            if (deep[e[i].u] < deep[e[i].v]) {
                swap(e[i].u, e[i].v);
            }
        }
        for (int i = 1; i <= n; i++) {
            posN[p[i]] = i;
            if (i != n) {
                posE[p[e[i].u]] = i;
            }
        }
        while (m--) {
            char str[10];
            int u, v, k;
            scanf("%s%d%d%d", str, &u, &v, &k);
            if (!strcmp(str, "ADD1")) {
                change(u, v, k, 0);
            } else {
                change(u, v, k, 1);
            }
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += c[i][0];
            ansN[posN[i]] = ans;
        }
        ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += c[i][1];
            ansE[posE[i]] = ans;
        }
        printf("Case #%d:\n", tt);
        for (int i = 1; i <= n; i++) {
            if (i == 1) {
                printf("%lld", ansN[i]);
            } else {
                printf(" %lld", ansN[i]);
            }
        }
        printf("\n");
        for (int i = 1; i < n; i++) {
            if (i == 1) {
                printf("%lld", ansE[i]);
            } else {
                printf(" %lld", ansE[i]);
            }
        }
        printf("\n");
    }
    return 0;
}