// Copyright 2022 NNTU-CS
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "tree.h"

PMTree::PMTree(std::vector<char> in) : root(new node(' ')) {
    add(root, in);
    generatePermutations();
}

PMTree::~PMTree() {
    clearTreeRecursive(root);
}

std::vector<char> PMTree::get1(int num) const {
    std::vector<std::vector<char>> all = permutations;
    if (num < 1 || num > static_cast<int>(all.size())) {
        return {};
    }
    return all[num - 1];
}

std::vector<char> PMTree::get2(int num) const {
    if (num < 1 || num > permutations.size() || !root) {
        return {};
    }

    std::vector<char> result;
    std::vector<char> elements;
    for (const auto& child : root->next) {
        elements.push_back(child->ch);
    }

    num--;

    while (!elements.empty()) {
        int fact = factorial(elements.size() - 1);
        int index = num / fact;
        result.push_back(elements[index]);
        elements.erase(elements.begin() + index);
        num %= fact;
    }

    return result;
}

std::vector<std::vector<char>> PMTree::generatePermutations() {
    permutations.clear();
    for (node* child : root->next) {
        std::vector<char> initialPermutation;
        genPermRecursive(child, initialPermutation);
    }
    return permutations;
}

void PMTree::add(node* current, std::vector<char> in) {
    if (in.empty()) {
        return;
    }
    for (size_t i = 0; i < in.size(); ++i) {
        char nextChar = in[i];
        node* newNode = new node(nextChar);
        current->next.push_back(newNode);
        std::vector<char> nextAvailableChars;
        for (size_t j = 0; j < in.size(); j++) {
            if (i != j) {
                nextAvailableChars.push_back(in[j]);
            }
        }
        add(newNode, nextAvailableChars);
    }
}

void PMTree::genPermRecursive(node* cur, std::vector<char> curPerm) {
    curPerm.push_back(cur->ch);
    if (cur->next.empty()) {
        permutations.push_back(curPerm);
        return;
    }
    for (node* child : cur->next) {
        genPermRecursive(child, curPerm);
    }
}

void PMTree::clearTreeRecursive(node* current) {
    if (current == nullptr) return;
    for (node* child : current->next) {
        clearTreeRecursive(child);
    }
    delete current;
}

int PMTree::countPermutations() const {
    return permutations.size();
}

bool PMTree::getPermRecursive(node* cur, int num, std::vector<char>& perm) {
    if (cur == nullptr) return false;
    if (cur == root) return true;

    perm.push_back(cur->ch);
    if (cur->next.empty()) {
        if (num == 1) {
            return true;
        } else {
            perm.pop_back();
            return false;
        }
    }

    for (node* child : cur->next) {
        int count = countPermutations();
        if (num <= count) {
            if (getPermRecursive(child, num, perm)) {
                return true;
            } else {
            }
        } else {
            num -= count;
        }
    }

    perm.pop_back();
    return false;
}

int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    return tree.get1(num);
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    return tree.get2(num);
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    return tree.generatePermutations();
}
