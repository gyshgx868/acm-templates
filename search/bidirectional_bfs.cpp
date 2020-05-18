// POJ 2243
struct Position {
  int x, y, step;
  Position(int _x, int _y, int _s): x(_x), y(_y), step(_s) { }
};
int vis[10][10];
int mark[10][10];
int sx, sy, ex, ey;
int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[] = {2, -2, 1, -1, 2, -2, -1, 1};
bool valid(int x, int y) {
  return x >= 0 && x < 8 && y >= 0 && y < 8;
}
int bfs() {
  std::queue<Position> qf, qb;
  memset(vis, 0, sizeof(vis));
  memset(mark, 0, sizeof(mark));
  qf.push(Position(sx, sy, 0));
  qb.push(Position(ex, ey, 1));
  vis[sx][sy] = 0;
  vis[ex][ey] = 1;
  mark[sx][sy] = 1;
  mark[ex][ey] = 2;
  while (!qf.empty() || !qb.empty()) {
    if (!qf.empty()) {
      Position p = qf.front();
      qf.pop();
      for (int i = 0; i < 8; ++i) {
        Position t = p;
        t.x += dx[i], t.y += dy[i];
        if (valid(t.x, t.y)) {
          if (mark[t.x][t.y] == 0) {
            vis[t.x][t.y] = vis[p.x][p.y] + 1;
            mark[t.x][t.y] = 1;
            qf.push(t);
          } else if (mark[t.x][t.y] == 2) {
            return vis[p.x][p.y] + vis[t.x][t.y];
          }
        }
      }
    }
    if (!qb.empty()) {
      Position p = qb.front();
      qb.pop();
      for (int i = 0; i < 8; ++i) {
        Position t = p;
        t.x += dx[i], t.y += dy[i];
        if (valid(t.x, t.y)) {
          if (mark[t.x][t.y] == 0) {
            vis[t.x][t.y] = vis[p.x][p.y] + 1;
            mark[t.x][t.y] = 2;
            qb.push(t);
          } else if (mark[t.x][t.y] == 1) {
            return vis[p.x][p.y] + vis[t.x][t.y];
          }
        }
      }
    }
  }
  return -1;
}
int main() {
  char s[5], e[5];
  while (~scanf("%s%s", s, e)) {
    sx = s[0] - 'a';
    sy = s[1] - '1';
    ex = e[0] - 'a';
    ey = e[1] - '1';
    int ans = bfs();
    if (!strcmp(s, e)) {
      printf("To get from %s to %s takes 0 knight moves.\n", s, e);
    } else {
      printf("To get from %s to %s takes %d knight moves.\n", s, e, ans);
    }
  }
  return 0;
}
