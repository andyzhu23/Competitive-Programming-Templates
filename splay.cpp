#include <vector>
#include <iostream>
namespace cp {
#ifndef CP_SPLAY_TREE
#define CP_SPLAY_TREE
template <typename T> class splay_tree {
    struct Node { int size, fa, lc, rc, cnt; T val; };

    int new_node(T x) { nodes.push_back({1, 0, 0, 0, 1, x}); return (int)nodes.size() - 1; }
    bool chk(int rt) const { return nodes[nodes[rt].fa].rc != rt; }

    void update(int rt) {
        nodes[rt].size = nodes[nodes[rt].lc].size + nodes[nodes[rt].rc].size + nodes[rt].cnt;
        nodes[nodes[rt].lc].fa = nodes[nodes[rt].rc].fa = rt;
    }
    void turn(int x) {
        int y = nodes[x].fa;
        int z = nodes[y].fa;
        int tmp;
        if(chk(x)) {
            tmp = nodes[x].rc;
            nodes[x].rc = y;
            nodes[y].lc = tmp;
        } else {
            tmp = nodes[x].lc;
            nodes[x].lc = y;
            nodes[y].rc = tmp;
        }
        nodes[tmp].fa = y;
        nodes[y].fa = x;
        nodes[x].fa = z;
        nodes[z].lc == y ? nodes[z].lc = x : nodes[z].rc = x;
        update(y);
        update(x);
    }
    void splay(int rt) {
        while(nodes[rt].fa) {
            if(nodes[nodes[rt].fa].fa) {
                if(chk(nodes[rt].fa) == chk(rt)) turn(nodes[rt].fa);
                else turn(rt);
            }
            turn(rt);
        }
        root = rt;
    }

    int insert_helper(int rt, T x) {
        if(rt == 0) return new_node(x);
        if(nodes[rt].val == x) ++nodes[rt].cnt;
        else if(nodes[rt].val > x) nodes[rt].lc = insert_helper(nodes[rt].lc, x);
        else nodes[rt].rc = insert_helper(nodes[rt].rc, x);
        update(rt);
        return rt;
    }
    int find_helper(int rt, T x) {
        if(rt == 0) return -1;
        if(nodes[rt].val == x) { splay(rt); return root; }
        else if(nodes[rt].val > x) return find_helper(nodes[rt].lc, x);
        else return find_helper(nodes[rt].rc, x);
    }
    int pre_helper(int rt, T x) const {
        if(rt == 0) return 0;
        if(nodes[rt].val < x) {
            int r = pre_helper(nodes[rt].rc, x);
            return r ? r : rt;
        }
        return pre_helper(nodes[rt].lc, x);
    }
    int succ_helper(int rt, T x) const {
        if(rt == 0) return 0;
        if(nodes[rt].val > x) {
            int r = succ_helper(nodes[rt].lc, x);
            return r ? r : rt;
        }
        return succ_helper(nodes[rt].rc, x);
    }
    int rnk_helper(int rt, T x) const {
        if(rt == 0) return 0;
        if(nodes[rt].val == x) return nodes[nodes[rt].lc].size + 1;
        else if(nodes[rt].val > x) return rnk_helper(nodes[rt].lc, x);
        else return rnk_helper(nodes[rt].rc, x) + nodes[nodes[rt].lc].size + nodes[rt].cnt;
    }
    T id_helper(int rt, int x) const {
        if(rt == 0) return T{};
        if(nodes[nodes[rt].lc].size >= x) return id_helper(nodes[rt].lc, x);
        else if(nodes[nodes[rt].lc].size + nodes[rt].cnt >= x) return nodes[rt].val;
        else return id_helper(nodes[rt].rc, x - nodes[nodes[rt].lc].size - nodes[rt].cnt);
    }
    int max_helper(int rt) const {
        return nodes[rt].rc ? max_helper(nodes[rt].rc) : rt;
    }
    int join(int x, int y) {
        if(x == 0 || y == 0) return x + y;
        int m = max_helper(x);
        splay(m);
        root = m;
        nodes[m].rc = y;
        nodes[y].fa = m;
        update(root);
        return m;
    }
    void print_subtree(int rt) const {
        if(rt == 0) return;
        const auto& n = nodes[rt];
        std::cout << "rt: " << rt << ", lc: " << n.lc << ", rc: " << n.rc
                  << ", sz: " << n.size << ", cnt: " << n.cnt << ", father: " << n.fa << '\n';
        print_subtree(n.lc);
        print_subtree(n.rc);
    }
    void inorder(std::ostream& os, int rt) const {
        if(rt == 0) return;
        inorder(os, nodes[rt].lc);
        for(int i = 0; i < nodes[rt].cnt; ++i) os << nodes[rt].val << ' ';
        inorder(os, nodes[rt].rc);
    }

public:
    splay_tree() : nodes(1) {} // index 0 is the sentinel; tree grows dynamically via push_back
    void reserve(int n) { nodes.reserve(n + 1); } // pre-allocate for n inserts (+1 for sentinel)

    void insert(T x) { root = insert_helper(root, x); splay(find_helper(root, x)); }
    int find(T x) { return find_helper(root, x); }
    int pre(T x) const { return pre_helper(root, x); }
    int succ(T x) const { return succ_helper(root, x); }
    int rnk(T x) const { return rnk_helper(root, x); }
    T id(int x) const { return id_helper(root, x); }
    int max() const { return max_helper(root); }
    void erase(T x) {
        int rt = find_helper(root, x);
        if(rt == -1 || rt == 0) return;
        if(--nodes[rt].cnt > 0) { update(rt); return; }
        root = join(nodes[rt].lc, nodes[rt].rc);
        nodes[root].fa = 0;
    }
    void print() const { print_subtree(root); }
    friend std::ostream& operator<<(std::ostream& os, const splay_tree& t) { t.inorder(os, t.root); return os; }

private:
    std::vector<Node> nodes;
    int root = 0;
};

#endif // CP_SPLAY_TREE
} // namespace cp
