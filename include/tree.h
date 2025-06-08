// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>
#include <iostream>

class PMTree {
private:
  struct node {
    char ch;
    std::vector<node*> next;
    node(char c) : ch(c) {}
  };
  node* root;
  std::vector<std::vector<char>> permutations;
  void add(node* current, std::vector<char> in);
  void generatePermutationsRecursive(node* current, std::vector<char> currentPermutation);
  void clearTreeRecursive(node* current);
  int countPermutations() const;
  bool getPermRecursive(node* current, int num, std::vector<char>& permutation);

public:
  PMTree(std::vector<char> in);
  ~PMTree();
  std::vector<std::vector<char>> generatePermutations();
  std::vector<char> get1(int num) const;
  std::vector<char> get2(int num) const;
};

int factorial(int n);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
std::vector<std::vector<char>> getAllPerms(PMTree& tree);

#endif  // INCLUDE_TREE_H_
