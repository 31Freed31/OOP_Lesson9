#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Branch {
public:
    std::string elfName;
    Branch* parent;
    std::vector<Branch> children;

    Branch(Branch* parentBranch = nullptr) : parent(parentBranch), elfName("None") {}

    Branch* findElf(const std::string& name) {
        if (elfName == name) return this;
        for (auto& child : children) {
            Branch* result = child.findElf(name);
            if (result != nullptr) return result;
        }
        return nullptr;
    }

    int countNeighbors() {
        if (parent == nullptr) return 0;

        int count = 0;
        for (auto& sibling : parent->children) {
            if (sibling.elfName != "None" && &sibling != this) {
                count++;
            }
            for (auto& child : sibling.children) {
                if (child.elfName != "None") count++;
            }
        }
        return count;
    }
};

class Tree {
public:
    Branch root;

    Tree() : root(nullptr) {}

    void generateBranches() {
        int numBigBranches = rand() % 3 + 3;
        for (int i = 0; i < numBigBranches; ++i) {
            root.children.emplace_back(&root);
            int numSmallBranches = rand() % 2 + 2;
            for (int j = 0; j < numSmallBranches; ++j) {
                root.children[i].children.emplace_back(&root.children[i]);
            }
        }
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");
    srand(static_cast<unsigned>(time(0)));

    std::vector<Tree> forest(5);
    for (int i = 0; i < 5; ++i) {
        forest[i].generateBranches();
    }

    std::cout << "Заселение эльфов. Введите имя или 'None', чтобы пропустить дом.\n";
    for (int treeIndex = 0; treeIndex < 5; ++treeIndex) {
        Tree& tree = forest[treeIndex];
        for (auto& bigBranch : tree.root.children) {
            std::cout << "Введите имя эльфа для большой ветви дерева " << treeIndex + 1 << ": ";
            std::cin >> bigBranch.elfName;
            for (auto& smallBranch : bigBranch.children) {
                std::cout << "Введите имя эльфа для средней ветви дерева " << treeIndex + 1 << ": ";
                std::cin >> smallBranch.elfName;
            }
        }
    }

    std::string elfNameToFind;
    std::cout << "Введите имя эльфа для поиска соседей: ";
    std::cin >> elfNameToFind;

    Branch* foundElf = nullptr;
    for (auto& tree : forest) {
        foundElf = tree.root.findElf(elfNameToFind);
        if (foundElf != nullptr) break;
    }

    if (foundElf != nullptr) {
        int neighbors = foundElf->countNeighbors();
        std::cout << "Эльф " << elfNameToFind << " имеет " << neighbors << " соседей на большой ветви.\n";
    }
    else {
        std::cout << "Эльф с именем " << elfNameToFind << " не найден.\n";
    }

    return 0;
}
