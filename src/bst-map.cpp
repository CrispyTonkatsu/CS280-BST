/**
 * @file bst-map.cpp
 * @author Edgar Jose Donoso Mansilla (e.donosomansilla)
 * @course CS280
 * @term Spring 2025
 *
 * @brief Implementation for a binary search tree
 */

#include <algorithm>
#include <list>
#include <optional>
#include <iostream>
#include <utility>
#include <vector>

#define BST_CPP

#ifndef BST_H
  #include "bst-map.h"
#endif

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
  BSTmap<K, V>::BSTmap(): root(nullptr), size_(0) {}

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap(const BSTmap& rhs): size_(rhs.size_) {
    if (rhs.root == nullptr) {
      return;
    }

    BSTmap& self = *this;

    std::list<Node*> insert_list{rhs.root};

    while (!insert_list.empty()) {
      Node* current = insert_list.front();

      self[current->Key()] = current->Value();

      if (current->left != nullptr) {
        insert_list.push_back(current->left);
      }

      if (current->right != nullptr) {
        insert_list.push_back(current->right);
      }

      insert_list.pop_front();
    }
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::operator=(const BSTmap& rhs) -> BSTmap& {
    if (this == &rhs) {
      return *this;
    }

    clear();

    if (rhs.root == nullptr) {
      return *this;
    }

    BSTmap& self = *this;

    std::list<Node*> insert_list{rhs.root};

    while (!insert_list.empty()) {
      Node* current = insert_list.front();

      self[current->Key()] = current->Value();

      if (current->left != nullptr) {
        insert_list.push_back(current->left);
      }

      if (current->right != nullptr) {
        insert_list.push_back(current->right);
      }

      insert_list.pop_front();
    }

    return *this;
  }

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap(BSTmap&& rhs):
      root(std::exchange(rhs.root, nullptr)),
      size_(std::exchange(rhs.size_, 0)) {}

  template<typename K, typename V>
  auto BSTmap<K, V>::operator=(BSTmap&& rhs) -> BSTmap& {
    clear();

    root = std::exchange(rhs.root, nullptr);
    size_ = std::exchange(rhs.size_, 0);

    return *this;
  }

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap::~BSTmap() {
    clear();
  }

  // Getters and setters

  template<typename K, typename V>
  auto BSTmap<K, V>::size() -> unsigned int {
    return size_;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::getdepth(Node*& node) const -> unsigned int {
    std::optional<NodeSearch> search = search_node(node->Key());
    if (search.has_value()) {
      return search.value().depth;
    }

    return 0;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::operator[](const K& key) -> V& {
    if (root == nullptr) {
      root = Node::CreateNode(key);
      size_++;
      return root->Value();
    }

    Node* current{root};

    while (current != nullptr) {
      if (key == current->Key()) {
        return current->Value();
      }

      if (key < current->Key()) {
        if (current->left == nullptr) {
          break;
        }

        current = current->left;
        continue;
      }

      if (key > current->Key()) {
        if (current->right == nullptr) {
          break;
        }

        current = current->right;
        continue;
      }
    }

    Node* to_add = Node::CreateNode(key);
    current->add_child(*to_add);
    size_++;

    return to_add->Value();
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::search_node(K key) const -> std::optional<NodeSearch> {
    if (root == nullptr) {
      return std::nullopt;
    }

    std::size_t depth = 0;
    Node* current{root};

    while (current != nullptr) {
      if (key == current->Key()) {
        return NodeSearch{*current, depth};
      }

      depth++;

      if (key < current->Key()) {
        if (current->left == nullptr) {
          break;
        }

        current = current->left;
        continue;
      }

      if (key > current->Key()) {
        if (current->right == nullptr) {
          break;
        }

        current = current->right;
        continue;
      }
    }

    return std::nullopt;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::clear() -> void {
    if (root == nullptr) {
      return;
    }

    std::list<Node*> deletion_queue{root};
    root = nullptr;

    while (!deletion_queue.empty()) {
      Node* to_delete = deletion_queue.front();

      if (to_delete->left != nullptr) {
        deletion_queue.push_back(to_delete->left);
      }

      if (to_delete->right != nullptr) {
        deletion_queue.push_back(to_delete->right);
      }

      deletion_queue.pop_front();

      size_--;
      delete to_delete;
    }
  }

  // Iterators

  template<typename K, typename V>
  auto BSTmap<K, V>::begin() -> iterator {
    if (root) {
      return iterator(root->first());
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
    std::optional<NodeSearch> search = search_node(key);
    if (search.has_value()) {
      return &search.value().node;
    }

    return end_it;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::erase(BSTmap_iterator it) -> void {
    if (it == end_it) {
      return;
    }

    Node* node = it.p_node;
    Node* parent = node->parent;

    if (!node->has_children()) {
      if (node->is_left_child()) {
        parent->left = nullptr;
      }

      if (node->is_right_child()) {
        parent->right = nullptr;
      }

      if (root == node) {
        root = nullptr;
      }

      size_--;
      delete node;
      return;
    }

    std::optional<Node*> only_child_opt = node->get_only_child();
    if (only_child_opt.has_value()) {
      Node* only_child = only_child_opt.value();

      if (node->is_left_child()) {
        parent->left = only_child;
      }

      if (node->is_right_child()) {
        parent->right = only_child;
      }

      if (root == node) {
        root = only_child;
      }

      only_child->parent = parent;

      size_--;
      delete node;
      return;
    }

    Node* predecessor = node->left->last();
    node->key = std::move(predecessor->key);
    node->value = std::move(predecessor->value);

    erase(iterator(predecessor));
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::begin() const -> const_iterator {
    if (root) {
      return const_iterator(root->first());
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
    std::optional<NodeSearch> search = search_node(key);
    if (search.has_value()) {
      return &search.value().node;
    }

    return end_it;
  }

  // Check Methods

  template<typename K, typename V>
  auto BSTmap<K, V>::sanityCheck() -> bool {
    if (root == nullptr) {
      return true;
    }

    std::list<Node*> insert_list{root};
    std::vector<K> seen_keys{};
    std::size_t measured_size{0};

    while (!insert_list.empty()) {
      Node* current = insert_list.front();

      if (std::find(seen_keys.begin(), seen_keys.end(), current->key)
          != seen_keys.cend()) {
        std::cout << "Found repeat key: " << current->key << std::endl;
        return false;
      }

      seen_keys.push_back(current->key);

      if (current->left != nullptr) {
        if (current->Value() <= current->left->Value()) {
          return false;
        }

        insert_list.push_back(current->left);
      }

      if (current->right != nullptr) {
        if (current->Value() >= current->right->Value()) {
          return false;
        }

        insert_list.push_back(current->right);
      }

      insert_list.pop_front();
      measured_size++;

      if (std::find(insert_list.begin(), insert_list.end(), current)
          != insert_list.cend()) {
        std::cout << "Circular reference found: Node of key =  " << current->key
                  << std::endl;
        return false;
      }
    }

    if (measured_size != size()) {
      return false;
    }

    return true;
  }

  /// Node Methods

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::CreateNode(K key) -> Node* {
    return new Node(key, V(), nullptr, 0, 0, nullptr, nullptr);
  }

  template<typename K, typename V>
  BSTmap<K, V>::Node::Node(K k, V val, Node* p, int h, int b, Node* l, Node* r):
      key(k), value(val), height(h), balance(b), parent(p), left(l), right(r) {}

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
  auto BSTmap<K, V>::Node::increment() -> Node* {
    // Searching right subtree
    if (right != nullptr) {
      return right->first();
    }

    // Searching left up-link
    Node* successor = this;

    while (successor != nullptr) {
      if (successor->is_left_child()) {
        return successor->parent;
      }

      successor = successor->parent;
    }

    return nullptr;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::decrement() -> Node* {
    // Searching left subtree
    if (left != nullptr) {
      return left->last();
    }

    // Searching right up-link
    Node* predecessor = this;

    while (predecessor != nullptr) {
      if (predecessor->is_right_child()) {
        return predecessor->parent;
      }

      predecessor = predecessor->parent;
    }

    return nullptr;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::print(std::ostream& os) const -> void {
    os << value;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::is_right_child() const -> bool {
    if (parent != nullptr) {
      return parent->right == this;
    }

    return false;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::is_left_child() const -> bool {
    if (parent != nullptr) {
      return parent->left == this;
    }

    return false;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::add_child(Node& node) -> void {
    if (node.Key() == key) {
      std::cout << "Attempted to add a child with the same key as the parent. "
                   "Doing nothing instead."
                << std::endl;
      return;
    }

    node.parent = this;

    if (node.Key() > key) {
      if (right != nullptr) {
        std::cout
          << "Attempted to add a child with the same key as the parent. "
             "Doing nothing instead."
          << std::endl;
        return;
      }

      right = &node;
    }

    if (node.Key() < key) {
      if (left != nullptr) {
        std::cout
          << "Attempted to add a child with the same key as the parent. "
             "Doing nothing instead."
          << std::endl;
        return;
      }

      left = &node;
    }
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::has_children() const -> bool {
    return (left != nullptr) || (right != nullptr);
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::Node::get_only_child() -> std::optional<Node*> {
    if (left != nullptr && right == nullptr) {
      return left;
    }

    if (left == nullptr && right != nullptr) {
      return right;
    }

    return std::nullopt;
  }

  // Iterator Methods

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap_iterator::BSTmap_iterator(Node* p): p_node(p) {}

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap_iterator::BSTmap_iterator(BSTmap_iterator& rhs):
      p_node(rhs.p_node) {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator=(const BSTmap_iterator& rhs)
    -> BSTmap_iterator& {
    p_node = rhs.p_node;
    return *this;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator++() -> BSTmap_iterator& {
    p_node = p_node->increment();
    return *this;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator++(int) -> BSTmap_iterator {
    BSTmap_iterator output = BSTmap_iterator(p_node);
    p_node = p_node->increment();
    return output;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator--() -> BSTmap_iterator& {
    p_node = p_node->decrement();
    return *this;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator--(int) -> BSTmap_iterator {
    BSTmap_iterator output = BSTmap_iterator(p_node);
    p_node = p_node->decrement();
    return output;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator*() -> Node& {
    return *p_node;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator->() -> Node* {
    return p_node;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator!=(const BSTmap_iterator& rhs)
    -> bool {
    return p_node != rhs.p_node;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator::operator==(const BSTmap_iterator& rhs)
    -> bool {
    return p_node == rhs.p_node;
  }

  // Const iterator_const Methods

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap_iterator_const::BSTmap_iterator_const(Node* p):
      p_node(p) {}

  template<typename K, typename V>
  BSTmap<K, V>::BSTmap_iterator_const::BSTmap_iterator_const(
    BSTmap_iterator_const& rhs
  ):
      p_node(rhs.p_node) {}

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator=(
    const BSTmap_iterator_const& rhs
  ) -> BSTmap_iterator_const& {
    p_node = rhs.p_node;
    return *this;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator++()
    -> BSTmap_iterator_const& {
    p_node = p_node->increment();
    return *this;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator++(int)
    -> BSTmap_iterator_const {
    BSTmap_iterator_const output = BSTmap_iterator_const(p_node);
    p_node = p_node->increment();
    return output;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator--()
    -> BSTmap_iterator_const& {
    p_node = p_node->decrement();
    return *this;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator--(int)
    -> BSTmap_iterator_const {
    BSTmap_iterator_const output = BSTmap_iterator_const(p_node);
    p_node = p_node->decrement();
    return output;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator*() -> const Node& {
    return *p_node;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator->() -> const Node* {
    return p_node;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator!=(
    const BSTmap_iterator_const& rhs
  ) -> bool {
    return p_node != rhs.p_node;
  }

  template<typename K, typename V>
  auto BSTmap<K, V>::BSTmap_iterator_const::operator==(
    const BSTmap_iterator_const& rhs
  ) -> bool {
    return p_node == rhs.p_node;
  }

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
    if (root) {
      BSTmap<K, V>::Node* b = root->last();
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
