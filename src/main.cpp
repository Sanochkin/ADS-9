// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include "time.h"
#include "tree.h"

#define A 20
#define B 30
#define C 40

int main() {
    std::vector<char> chars1;
    std::vector<char> chars2;
    std::vector<char> chars3;

    for (int i = 0; i < A; i++) {
        chars1.push_back(static_cast<char>(i));
    }
    for (int i = 0; i < B; i++) {
        chars2.push_back(static_cast<char>(i));
    }
    for (int i = 0; i < C; i++) {
        chars3.push_back(static_cast<char>(i));
    }

    PMTree tree1(chars1);
    PMTree tree2(chars2);
    PMTree tree3(chars3);

    int begin1 = clock();
    std::vector<std::vector<char>> permutations1 = getAllPerms(tree1);
    int end1 = clock();
    int begin2 = clock();
    std::vector<std::vector<char>> permutations2 = getAllPerms(tree2);
    int end2 = clock();
    int begin3 = clock();
    std::vector<std::vector<char>> permutations3 = getAllPerms(tree3);
    int end3 = clock();
    int t1 = end1 - begin1;
    int t2 = end2 - begin2;
    int t3 = end3 - begin3;
    std::cout << "t p1: " << t1 << " t p2: " << t2 << " t p3: " << t3 << '\n';

    unsigned int seed1 = 12345;
    unsigned int seed2 = 67890;
    unsigned int seed3 = 13579;

    int rand_num1 = (rand_r(&seed1) % permutations1) + 1;
    int rand_num2 = (rand_r(&seed2) % permutations2) + 1;
    int rand_num3 = (rand_r(&seed3) % permutations3) + 1;

    int begin1_1 = clock();
    std::vector<char> rand1_1 = getPerm1(tree1, rand_num1);
    int end1_1 = clock();
    int t1_1 = end1_1 - begin1_1;
    int begin1_2 = clock();
    std::vector<char> rand1_2 = getPerm2(tree1, rand_num1);
    int end1_2 = clock();
    int t1_2 = end1_2 - begin1_2;

    int begin2_1 = clock();
    std::vector<char> rand2_1 = getPerm1(tree2, rand_num2);
    int end2_1 = clock();
    int t2_1 = end2_1 - begin2_1;
    int begin2_2 = clock();
    std::vector<char> rand2_2 = getPerm2(tree2, rand_num2);
    int end2_2 = clock();
    int t2_2 = end2_2 - begin2_2;

    int begin3_1 = clock();
    std::vector<char> rand3_1 = getPerm1(tree3, rand_num3);
    int end3_1 = clock();
    int t3_1 = end3_1 - begin3_1;
    int begin3_2 = clock();
    std::vector<char> rand3_2 = getPerm2(tree3, rand_num3);
    int end3_2 = clock();
    int t3_2 = end3_2 - begin3_2;
    std::cout << t1_1 << " " << t1_2 << " ";
    std::cout << t2_1 << " " << t2_2 << " ";
    std::cout << t3_1 << " " << t3_2 << " ";
    return 0;
}
