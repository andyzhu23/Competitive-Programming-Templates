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

    // every search splays the deepest touched node to preserve amortized O(log n)
    void insert(T x) {
        if(root == 0) { root = new_node(x); return; }
        int rt = root, last = 0;
        while(rt) {
            last = rt;
            if(nodes[rt].val == x) { ++nodes[rt].cnt; update(rt); splay(rt); return; }
            rt = nodes[rt].val > x ? nodes[rt].lc : nodes[rt].rc;
        }
        int n = new_node(x);
        (nodes[last].val > x ? nodes[last].lc : nodes[last].rc) = n;
        nodes[n].fa = last;
        splay(n);
    }
    int find(T x) {
        int rt = root, last = 0;
        while(rt) {
            last = rt;
            if(nodes[rt].val == x) { splay(rt); return root; }
            rt = nodes[rt].val > x ? nodes[rt].lc : nodes[rt].rc;
        }
        if(last) splay(last);
        return -1;
    }
    int pre(T x) {
        int rt = root, last = 0, ans = 0;
        while(rt) {
            last = rt;
            if(nodes[rt].val < x) { ans = rt; rt = nodes[rt].rc; }
            else rt = nodes[rt].lc;
        }
        if(ans) { splay(ans); return root; }
        if(last) splay(last);
        return 0;
    }
    int succ(T x) {
        int rt = root, last = 0, ans = 0;
        while(rt) {
            last = rt;
            if(nodes[rt].val > x) { ans = rt; rt = nodes[rt].lc; }
            else rt = nodes[rt].rc;
        }
        if(ans) { splay(ans); return root; }
        if(last) splay(last);
        return 0;
    }
    int rnk(T x) {
        int rt = root, last = 0, ans = 0;
        while(rt) {
            last = rt;
            if(nodes[rt].val == x) { ans += nodes[nodes[rt].lc].size + 1; splay(rt); return ans; }
            if(nodes[rt].val > x) rt = nodes[rt].lc;
            else { ans += nodes[nodes[rt].lc].size + nodes[rt].cnt; rt = nodes[rt].rc; }
        }
        if(last) splay(last);
        return ans;
    }
    T id(int x) {
        int rt = root, last = 0;
        while(rt) {
            last = rt;
            int lsz = nodes[nodes[rt].lc].size;
            if(lsz >= x) rt = nodes[rt].lc;
            else if(lsz + nodes[rt].cnt >= x) { splay(rt); return nodes[root].val; }
            else { x -= lsz + nodes[rt].cnt; rt = nodes[rt].rc; }
        }
        if(last) splay(last);
        return T{};
    }
    int max() {
        if(root == 0) return 0;
        int rt = root;
        while(nodes[rt].rc) rt = nodes[rt].rc;
        splay(rt);
        return root;
    }
    void erase(T x) {
        int rt = find(x);
        if(rt == -1) return;
        if(--nodes[rt].cnt > 0) { update(rt); return; }
        int l = nodes[rt].lc, r = nodes[rt].rc;
        nodes[l].fa = nodes[r].fa = 0;
        if(l == 0) { root = r; return; }
        if(r == 0) { root = l; return; }
        int m = l;
        while(nodes[m].rc) m = nodes[m].rc;
        root = l;
        splay(m);
        nodes[m].rc = r;
        nodes[r].fa = m;
        update(m);
    }
    void print() const { print_subtree(root); }
    friend std::ostream& operator<<(std::ostream& os, const splay_tree& t) { t.inorder(os, t.root); return os; }

private:
    std::vector<Node> nodes;
    int root = 0;
};

#endif // CP_SPLAY_TREE
} // namespace cp
