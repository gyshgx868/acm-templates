std::set<int, std::less<int> > s1;     // 升序排列
std::set<int, std::greater<int> > s2;  // 降序排列
std::multiset<int> s3;
// 和其他容器一样, set也可以用预定义的区间来初始化

// 查询
s.count(10);  // 返回s中值为10的具体数目, 但对于set来说, 返回值是0或1
s.empty();    // 判断集合是否为空集
s.size();     // 返回集合的元素数量

// 插入和删除
s.insert(e);           // 将e插入到set中
// 注意, insert的返回值是一个pair, 其first是指向插入后元素的迭代器, 
// second表示插入是否成功 (如果其second为false, 说明元素已经存在)
s.insert(begin, end);  // 将区间[begin, end)中的值插入到s中
s.erase(e);            // 将e删除并返回剩余的e的数量
s.erase(pos);          // 将pos处的元素删除
s.erase(begin, end);   // 将[begin, end)处的元素删除

// 迭代器: begin、end、rbegin、rend分别返回正向和反向迭代器
