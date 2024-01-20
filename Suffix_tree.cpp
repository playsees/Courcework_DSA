#include <iostream>
#include <vector>
#include <string>
#include <functional>

struct Node {
    std::string sub = "";   
    std::vector<int> ch;    

    Node() {
        
    }

    Node(const std::string& sub, std::initializer_list<int> children) : sub(sub) {
        ch.insert(ch.end(), children);
    }
};

struct SuffixTree {
    std::vector<Node> nodes;

    SuffixTree(const std::string& str) {
        nodes.push_back(Node{});
        for (size_t i = 0; i < str.length(); i++) {
            addSuffix(str.substr(i));
        }
    }

    void visualize() {
        if (nodes.size() == 0) {
            std::cout << "\n";
            return;
        }

        std::function<void(int, const std::string&)> f;
        f = [&](int n, const std::string & pre) {
            auto children = nodes[n].ch;
            if (children.size() == 0) {
                std::cout << "- " << nodes[n].sub << '\n';
                return;
            }
            std::cout << "+ " << nodes[n].sub << '\n';

            auto it = std::begin(children);
            if (it != std::end(children)) do {
                if (std::next(it) == std::end(children)) break;
                std::cout << pre << "+-";
                f(*it, pre + "| ");
                it = std::next(it);
            } while (true);

            std::cout << pre << "+-";
            f(children[children.size() - 1], pre + "  ");
        };

        f(0, "");
    }

private:
    void addSuffix(const std::string & suf) {
        int n = 0;
        size_t i = 0;
        while (i < suf.length()) {
            char b = suf[i];
            int x2 = 0;
            int n2;
            while (true) {
                auto children = nodes[n].ch;
                if (x2 == children.size()) {
                    
                    n2 = nodes.size();
                    nodes.push_back(Node(suf.substr(i), {}));
                    nodes[n].ch.push_back(n2);
                    return;
                }
                n2 = children[x2];
                if (nodes[n2].sub[0] == b) {
                    break;
                }
                x2++;
            }
           
            auto sub2 = nodes[n2].sub;
            size_t j = 0;
            while (j < sub2.size()) {
                if (suf[i + j] != sub2[j]) {
                    // split n2
                    auto n3 = n2;
                  
                    n2 = nodes.size();
                    nodes.push_back(Node(sub2.substr(0, j), { n3 }));
                    nodes[n3].sub = sub2.substr(j); 
                    nodes[n].ch[x2] = n2;
                    break; 
                }
                j++;
            }
            i += j; 
            n = n2; 
        }
    }
};

int main() {
    SuffixTree("banana$").visualize();
}
