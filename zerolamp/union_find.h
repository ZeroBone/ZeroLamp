#ifndef ZB_UNION_FIND_H
#define ZB_UNION_FIND_H

#include <Arduino.h>
#include <vector>

template <typename I>
struct RankPointer {
  I parent;
  I rank;

  RankPointer(I parent, I rank) : parent(parent), rank(rank) {}
  RankPointer() {}

};

// union-find datastructure with union-by-rank and path compression
template <typename I>
class UnionFind {

private:
  RankPointer<I>* pointers;

public:
  UnionFind(I capacity) {
    pointers = new RankPointer<I>[capacity];

    for (I i = 0; i < capacity; i++) {
      pointers[i] = RankPointer<I>(i, 0);
    }
  }

  ~UnionFind() {
    delete[] pointers;
  }

  I find_root(I x) {

    std::vector<I> path; // the path we move along when looking for the root

    while (pointers[x].parent != x) {
      path.push_back(x);
      x = pointers[x].parent;
    }

    // path compression: update all parent pointers along the path to point directly at the root
    for (I el : path) {
      pointers[el].parent = x;
    }

    return x;

  }

  bool in_same_set(I x, I y) {
    return find_root(x) == find_root(y);
  }

  void merge(I a, I b) {

    I a_root = find_root(a);
    I b_root = find_root(b);

    if (a_root == b_root) {
      // same disjoint set, nothing to union
      return;
    }

    if (pointers[a_root].rank > pointers[b_root].rank) {
      // make b set child of a set
      pointers[b_root].parent = a_root;
    }
    else if (pointers[a_root].rank < pointers[b_root].rank) {
      // make a set child of b set
      pointers[a_root].parent = b_root;
    }
    else {
      // make a set child of b set
      // and increase rank of b
      pointers[a_root].parent = b_root;
      pointers[b_root].rank++;
    }

  }

};

#endif