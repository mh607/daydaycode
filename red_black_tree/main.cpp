/*
红黑树是一种自平衡二叉搜索树，具有以下性质：
1. 每个节点要么是红色，要么是黑色。
2. 根节点是黑色。
3. 每个叶子节点（NIL节点）是黑色。
4. 如果一个节点是红色的，则它的两个子节点都是黑色的
5. 从任一节点到其每个叶子节点的所有路径都包含相同数目的黑色节点。
红黑树的插入和删除操作通过旋转和重新着色来保持树的平衡，从而确保在最坏情况下的时间复杂度为O(log n)。红黑树广泛应用于各种数据结构和算法中，如关联数组、集合等。
插入：
1. 将新节点插入到适当的位置，并将其颜色设置为红色。
2. 如果新节点的父节点是黑色的，则插入完成。
3. 如果新节点的父节点是红色的，则需要进行调整：
   a. 如果叔叔节点是红色的，则将父节点和叔叔节点重新着色为黑色，并将祖父节点重新着色为红色，然后继续调整祖父节点。
   b. 如果叔叔节点是黑色的，则需要进行旋转      
        i. 如果新节点是父节点的右子节点，则进行左旋转。
        ii. 将父节点重新着色为黑色，祖父节点重新着色为红色，然后进行右旋转。
删除：
1. 如果要删除的节点有两个子节点，则找到其后继节点（右子树中的最小节点），将其值复制到要删除的节点，然后删除后继节点。
2. 如果要删除的节点有一个子节点或没有子节点，则直接删除该节点。
3. 如果删除的节点是黑色的，则需要进行调整：
   a. 如果替代节点是红色的，则将其重新着色为黑色。
   b. 如果替代节点是黑色的，则需要进行旋转和重新着色来保持树的平衡。
        i. 如果替代节点是左子节点，则进行右旋转。
        ii. 如果替代节点是右子节点，则进行左旋转。
        iii. 将父节点重新着色为黑色，兄弟节点重新着色为红色，然后继续调整父节点。   
*/
#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
};

class RBTree {
private:
    Node* root;  // 红黑树的根节点
    Node* NIL;   // 哨兵节点，表示叶子节点，所有叶子都指向NIL

    // 左旋转操作：围绕节点x进行左旋转
    void left_rotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // 右旋转操作：围绕节点x进行右旋转
    void right_rotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // 插入修复：插入新节点后，通过旋转和重新着色保持红黑树性质
    void insert_fixup(Node* z) {
        while (z->parent != nullptr && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;  // 叔叔节点
                if (y->color == RED) {
                    // 情况1：叔叔节点是红色
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        // 情况2：叔叔节点是黑色，且z是右子节点
                        z = z->parent;
                        left_rotate(z);
                    }
                    // 情况3：叔叔节点是黑色，且z是左子节点
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    right_rotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;  // 叔叔节点
                if (y->color == RED) {
                    // 情况1：叔叔节点是红色
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        // 情况2：叔叔节点是黑色，且z是左子节点
                        z = z->parent;
                        right_rotate(z);
                    }
                    // 情况3：叔叔节点是黑色，且z是右子节点
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    left_rotate(z->parent->parent);
                }
            }
        }
        if (root != nullptr) root->color = BLACK;
    }

    // 移植操作：将子树v移植到u的位置
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // 找到以x为根的子树中的最小节点
    Node* minimum(Node* x) {
        while (x->left != NIL) {
            x = x->left;
        }
        return x;
    }

    // 删除修复：删除节点后，通过旋转和重新着色保持红黑树性质
    void delete_fixup(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;  // 兄弟节点
                if (w->color == RED) {
                    // 情况1：兄弟节点是红色
                    w->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    // 情况2：兄弟节点的两个子节点都是黑色
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        // 情况3：兄弟节点的右子节点是黑色
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    // 情况4：兄弟节点的右子节点是红色
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;  // 兄弟节点
                if (w->color == RED) {
                    // 情况1：兄弟节点是红色
                    w->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    // 情况2：兄弟节点的两个子节点都是黑色
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        // 情况3：兄弟节点的左子节点是黑色
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    // 情况4：兄弟节点的左子节点是红色
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

public:
    // 构造函数：初始化红黑树
    RBTree() {
        NIL = new Node{0, BLACK, nullptr, nullptr, nullptr};  // 创建哨兵节点
        root = NIL;
    }

    // 析构函数：清理内存
    ~RBTree() {
        delete_tree(root);  // 递归删除所有节点
        delete NIL;         // 删除哨兵节点
    }

    // 递归删除树中的所有节点
    void delete_tree(Node* node) {
        if (node != NIL) {
            delete_tree(node->left);
            delete_tree(node->right);
            delete node;
        }
    }

    // 插入新键值
    void insert(int key) {
        Node* z = new Node{key, RED, NIL, NIL, nullptr};  // 新节点初始为红色
        Node* y = nullptr;
        Node* x = root;
        // 找到插入位置
        while (x != NIL) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nullptr) {
            root = z;  // 树为空，新节点为根
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
        // 如果父节点为空，设为黑色
        if (z->parent == nullptr) {
            z->color = BLACK;
            return;
        }
        // 如果祖父节点为空，无需修复
        if (z->parent->parent == nullptr) {
            return;
        }
        insert_fixup(z);  // 修复红黑树性质
    }

    // 删除指定键值的节点
    void remove(int key) {
        Node* z = root;
        // 找到要删除的节点
        while (z != NIL) {
            if (key == z->key) {
                break;
            } else if (key < z->key) {
                z = z->left;
            } else {
                z = z->right;
            }
        }
        if (z == NIL) {
            return;  // 节点不存在
        }
        Node* y = z;
        Node* x;
        Color y_original_color = y->color;
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);  // 找到后继节点
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;  // 删除节点
        if (y_original_color == BLACK) {
            delete_fixup(x);  // 如果删除的是黑色节点，需要修复
        }
    }

    // 中序遍历打印树
    void inorder_traversal(Node* node) {
        if (node != NIL) {
            inorder_traversal(node->left);
            std::cout << node->key << " ";
            inorder_traversal(node->right);
        }
    }

    // 打印中序遍历结果
    void print_inorder() {
        inorder_traversal(root);
        std::cout << std::endl;
    }
};

int main() {
    std::cout << "Start" << std::endl;
    RBTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    std::cout << "插入后中序遍历: ";
    tree.print_inorder();

    tree.remove(20);
    std::cout << "删除20后中序遍历: ";
    tree.print_inorder();

    tree.remove(10);
    std::cout << "删除10后中序遍历: ";
    tree.print_inorder();

    return 0;
}
