// Copyright 2022 NNTU-CS
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "tree.h"

PMTree::PMTree(std::vector<char> in) : root(new node(' ')) {
    add(root, in);
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
        generatePermutationsRecursive(child, initialPermutation);
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

void PMTree::generatePermutationsRecursive(node* current, std::vector<char> currentPermutation) {
    currentPermutation.push_back(current->ch);
    if (current->next.empty()) {
        permutations.push_back(currentPermutation);
        return;
    }
    for (node* child : current->next) {
        generatePermutationsRecursive(child, currentPermutation);
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

bool PMTree::getPermRecursive(node* current, int num, std::vector<char>& permutation) {
    if (current == nullptr) return false;
    if (current == root) return true;

    permutation.push_back(current->ch);
    if (current->next.empty()) {
        if (num == 1) {
            return true;
        }
        else {
            permutation.pop_back();
            return false;
        }
    }

    for (node* child : current->next) {
        int count = countPermutations();
        if (num <= count) {
            if (getPermRecursive(child, num, permutation)) {
                return true;
            }
            else {
            }
        }
        else {
            num -= count;
        }
    }

    permutation.pop_back();
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
