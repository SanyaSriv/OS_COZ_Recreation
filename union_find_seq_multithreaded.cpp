// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <random>
#include <thread>
#include <coz.h>

using namespace std;

class UnionFind {
    public:
        UnionFind(int n);
        int find_elem(int elem);
        void union_elem(int a, int b);
        void unmerge(int a);
    private:
        vector<int> parent;
};

UnionFind::UnionFind(int n) {
    // there will be no parents and all elements
    // will be separate
    for (int i = 0; i < n; i ++) {
        parent.push_back(i);
        // indicating all the elemets are in their own sets for now
    }
}

int UnionFind::find_elem(int elem) {
    if (parent[elem] == elem) {
        // elem is in its own set
        return parent[elem];
    }
    parent[elem] = find_elem(parent[elem]);
    return parent[elem];
}

void UnionFind::union_elem(int a, int b) {
    COZ_PROGRESS;
    int a_root = find_elem(a);
    int b_root = find_elem(b);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(1, 1000);
    int r = dis(gen);
    if (r % 2 == 0) {
        // merge b's set into a
        parent[b_root] = a_root;
    } else {
        // merge a's set into b
        parent[a_root] = b_root;
    }
}

void UnionFind::unmerge(int a) {
    // make a its own parent
    parent[a] = a;
}

void thread_1_function(UnionFind object) {
    for (int i = 0; i < 2000000; i++) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(0, 300000);
        int r1 = dis(gen);
        object.find_elem(r1);
    }
}

void thread_2_function(UnionFind object) {
    for (int i = 0; i < 2000000; i++) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(0, 300000);
        int r1 = dis(gen);
        int r2 = dis(gen);
        object.union_elem(r1, r2);
    }
}

void thread_3_function(UnionFind object) {
    for (int i = 0; i < 2000000; i++) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(0, 300000);
        int r1 = dis(gen);
        object.unmerge(r1);
    }
}

int main() {
    // Write C++ code here
    UnionFind object(300000);
    thread uf[4];
    uf[0] = thread(thread_1_function, object);
    uf[1] = thread(thread_2_function, object);
    uf[2] = thread(thread_3_function, object);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 3);
    int r1 = dis(gen);
    if (r1 % 3 == 0) {
        uf[3] = thread(thread_1_function, object);
    } else if (r1 % 3 == 1) {
        uf[3] = thread(thread_2_function, object);
    } else {
        uf[3] = thread(thread_3_function, object);
    }
    uf[0].join();
    uf[1].join();
    uf[2].join();
    uf[3].join();
    COZ_PROGRESS;
    return 0;
}
