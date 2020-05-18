// m[key] = value;
// map按照key值排序
std::map<int, int> m;                      // 按照key从小到大排序
std::map<int, int, std::greater<int> > m;  // 按照key从大到小排序

// map按照value值排序
// 使用vector
typedef std::pair<int, int> PII;
std::vector<PII> v;
bool cmp(const PII& a, const PII& b) {
  return a.second > b.second;
}
for (std::map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
  v.push_back(*it);
}
sort(v.begin(), v.end());
// 使用map
std::map<int, int> tmp;
for (std::map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
  tmp[(*.it).second] = (*.it).first;
}

// map中元素的查找
// find()函数返回一个迭代器指向键值为key的元素, 如果没找到就返回指向map尾部的迭代器
std::map<int, string>::iterator it;
it = m.find(112);
if (it == m.end()) {
  cout << "Not Found." << endl;
} else {
  cout << "Found." << endl;
}

// map中元素的删除
std::map<int, string>::iterator it;
it = m.find(112);
if (it != m.end()) {
  m.erase(it);
}

// map的基本操作函数：
// C++ Maps是一种关联式容器，包含“关键字/值”对
begin()          // 返回指向map头部的迭代器
clear()          // 删除所有元素
count()          // 返回指定元素出现的次数
empty()          // 如果map为空则返回true
end()            // 返回指向map末尾的迭代器
equal_range()    // 返回特殊条目的迭代器对
erase()          // 删除一个元素
find()           // 查找一个元素
get_allocator()  // 返回map的配置器
insert()         // 插入元素
key_comp()       // 返回比较元素key的函数
lower_bound()    // 返回键值>=给定元素的第一个位置
max_size()       // 返回可以容纳的最大元素个数
rbegin()         // 返回一个指向map尾部的逆向迭代器
rend()           // 返回一个指向map头部的逆向迭代器
size()           // 返回map中元素的个数
swap()           // 交换两个map
upper_bound()    // 返回键值>给定元素的第一个位置
value_comp()     // 返回比较元素value的函数
