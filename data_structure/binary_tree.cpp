template <class T>
struct TreeNode {
  T data;
  TreeNode* left;
  TreeNode* right;

  TreeNode() : left(nullptr), right(nullptr) {}

  explicit TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr)
      : data(x), left(l), right(r) {}
};

template <class T>
class BinaryTree {
 public:
  explicit BinaryTree(TreeNode<T>* t = nullptr) : root(t) {}

  ~BinaryTree() { destroy(root); }

  bool empty() const { return root == nullptr; }

  TreeNode<T>* left_child(TreeNode<T>* t) {
    return t != nullptr ? t->left : nullptr;
  }

  TreeNode<T>* right_child(TreeNode<T>* t) {
    return t != nullptr ? t->right : nullptr;
  }

  TreeNode<T>* get_root() const { return root; }

 private:
  TreeNode<T>* root;

  void destroy(TreeNode<T>*& subTree) {
    if (subTree != nullptr) {
      destroy(subTree->left);
      destroy(subTree->right);
      delete subTree;
    }
  }
};

// 根据前序序列 (VLR) 和中序序列 (LVR) 构造二叉树
template <class T>
TreeNode<T>* create_tree(int* vlr, int* lvr, int n) {
  if (n == 0) { return nullptr; }
  int k = 0;
  while (vlr[0] != lvr[k]) { k++; }
  TreeNode<T>* res = new TreeNode<T>(vlr[0]);
  res->left = create_tree<T>(vlr + 1, lvr, k);
  res->right = create_tree<T>(vlr + k + 1, lvr + k + 1, n - k - 1);
  return res;
}
