#define BST_CPP

#ifndef BST_H
  #include "bst-map.h"
#endif

#include <iostream>

namespace CS280 {

  // static data members
  template<typename K, typename V>
  typename BSTmap<K, V>::iterator BSTmap<K, V>::end_it{
    nullptr,
  };

  template<typename K, typename V>
  typename BSTmap<K, V>::const_iterator BSTmap<K, V>::const_end_it{
    nullptr,
  };

  /// BST Methods

  // Constructors & Destructor

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap(): pRoot(nullptr), size_(0) {}

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap(const BSTmap& rhs) // : // ....
  {
    // ...
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::operator=(const BSTmap& rhs) -> BSTmap& // ....
  {
    // ...
  }

  // Lovely lookup space qualifications -> (BSTmap::BSTmap::~BSTmap) <3
  template<typename K, typename V>
  BSTmap<K, V>::BSTmap::~BSTmap() {}

  // Getters and setters

  template<typename K, typename V>
  auto BSTmap<K, V>::size() -> unsigned int {
    return size_;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::getdepth(Node*& node) const -> unsigned int {
    return 0;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::operator[](const K& key) -> V& {}

  // Iterators

  template<typename K, typename V>
  auto BSTmap<K, V>::begin() -> iterator {
    if (pRoot) {
      return iterator(pRoot->first());
    } else {
      return end_it;
    }
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::end() -> iterator {
    return end_it;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::find(const K& key) -> iterator {
    return end_it;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::erase(BSTmap_iterator it) -> void {}

  template<typename K, typename V>
  auto BSTmap<K, V>::begin() const -> const_iterator {
    if (pRoot) {
      return const_iterator(pRoot->first());
    } else {
      return end_it;
    }
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::end() const -> const_iterator {
    return end_it;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::find(const K& key) const -> const_iterator {
    return end_it;
  }

  // Check Methods

  template<typename K, typename V>
  auto BSTmap<K, V>::sanityCheck() -> bool {
    return false;
  }

  /// Node Methods

  template<typename K, typename V>
  BSTmap<K, V>::Node::Node(K k, V val, Node* p, int h, int b, Node* l, Node* r):
      key(k), value(val), parent(p), height(h), balance(b), left(l), right(r) {}

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::Key() const -> const K& {
    return key;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::Value() -> V& {
    return value;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::first() -> Node* {
    if (left == nullptr) {
      return this;
    }

    return left->first();
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::last() -> Node* {
    if (right == nullptr) {
      return this;
    }

    return right->last();
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::increment() -> Node* {}

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::decrement() -> Node* {}

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::print(std::ostream& os) const -> void {
    // NOTE: Make sure that std::endl is not needed here
    os << value;
  }

  // Iterator Methods

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap_iterator::BSTmap_iterator(Node* p) {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator=(const BSTmap_iterator& rhs)
    -> BSTmap_iterator& {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator++() -> BSTmap_iterator& {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator++(int) -> BSTmap_iterator {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator*() -> Node& {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator->() -> Node* {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator!=(const BSTmap_iterator& rhs)
    -> bool {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator==(const BSTmap_iterator& rhs)
    -> bool {}

  // Const iterator_const Methods

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap_iterator_const::BSTmap_iterator_const(Node* p) {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator=(const BSTmap_iterator& rhs
  ) -> BSTmap_iterator_const& {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator++()
    -> BSTmap_iterator_const& {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator++(int)
    -> BSTmap_iterator_const {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator*() -> Node& {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator->() -> Node* {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator!=(
    const BSTmap_iterator_const& rhs
  ) -> bool {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator==(
    const BSTmap_iterator_const& rhs
  ) -> bool {}

  ////////////////////////////////////////////////////////////
  // do not change this code from here to the end of the file
  /* figure out whether node is left or right child or root
   * used in print_backwards_padded
   */
  template<typename K, typename V>
  auto BSTmap<K, V>::get_edge_symbol(const Node* node) const -> char {
    const Node* parent = node->parent;
    if (parent == nullptr) {
      return '-';
    } else {
      return (parent->left == node) ? '\\' : '/';
    }
  }

  /* this is another "ASCII-graphical" print, but using
   * iterative function.
   * Left branch of the tree is at the bottom
   */
  template<typename K, typename V>
  auto operator<<(std::ostream& os, const BSTmap<K, V>& map) -> std::ostream& {
    map.print(os);
    return os;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::print(std::ostream& os, bool print_value) const -> void {
    if (pRoot) {
      BSTmap<K, V>::Node* b = pRoot->last();
      while (b) {
        int depth = getdepth(b);
        int i;
        /* printf(b); */

        char edge = get_edge_symbol(b);
        switch (edge) {
          case '-':
            for (i = 0; i < depth; ++i) {
              std::printf("       ");
            }
            os << b->key;
            if (print_value) {
              os << " -> " << b->value;
            }
            os << std::endl;
            break;
          case '\\':
            for (i = 0; i < depth; ++i) {
              std::printf("       ");
            }
            os << edge << std::endl;
            for (i = 0; i < depth; ++i) {
              std::printf("       ");
            }
            os << b->key;
            if (print_value) {
              os << " -> " << b->value;
            }
            os << std::endl;
            break;
          case '/':
            for (i = 0; i < depth; ++i) {
              std::printf("       ");
            }
            os << b->key;
            if (print_value) {
              os << " -> " << b->value;
            }
            os << std::endl;
            for (i = 0; i < depth; ++i) {
              std::printf("       ");
            }
            os << edge << std::endl;
            break;
        }
        b = b->decrement();
      }
    }
    std::printf("\n");
  }
} // namespace CS280
