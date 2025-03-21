#ifndef BSTMAP_H
#define BSTMAP_H

#include <iosfwd>

namespace CS280 {

  template<typename K, typename V>
  class BSTmap {
    struct BSTmap_iterator;
    struct BSTmap_iterator_const;

  public:

    // standard names for iterator types
    typedef BSTmap_iterator iterator;
    typedef BSTmap_iterator_const const_iterator;

    class Node {
    public:

      Node(K k, V val, Node* p, int h, int b, Node* l, Node* r);

      Node(const Node&) = delete;
      auto operator=(const Node&) -> Node& = delete;

      auto Key() const -> const K&; // return a const reference
      auto Value() -> V&;           // return a reference

      auto first() -> Node*;        // minimum - follow left as far as possible
      auto last() -> Node*;         // maximum - follow right as far as possible
      auto increment() -> Node*;    // successor
      auto decrement() -> Node*;    // predecessor
      auto print(std::ostream& os) const -> void;

    private:

      auto is_parent_left() const -> bool;

      K key;
      V value;
      int height, balance; // optional
      Node* parent;
      Node* left;
      Node* right;

      friend class BSTmap;
    };

  private:

    struct BSTmap_iterator {
    private:

      Node* p_node;

    public:

      BSTmap_iterator(Node* p = nullptr);
      auto operator=(const BSTmap_iterator& rhs) -> BSTmap_iterator&;
      auto operator++() -> BSTmap_iterator&;
      auto operator++(int) -> BSTmap_iterator;
      auto operator*() -> Node&;
      auto operator->() -> Node*;
      auto operator!=(const BSTmap_iterator& rhs) -> bool;
      auto operator==(const BSTmap_iterator& rhs) -> bool;

      friend class BSTmap;
    };

    struct BSTmap_iterator_const {
    private:

      Node* p_node;

    public:

      BSTmap_iterator_const(Node* p = nullptr);
      auto operator=(const BSTmap_iterator& rhs) -> BSTmap_iterator_const&;
      auto operator++() -> BSTmap_iterator_const&;
      auto operator++(int) -> BSTmap_iterator_const;
      auto operator*() -> Node&;
      auto operator->() -> Node*;
      auto operator!=(const BSTmap_iterator_const& rhs) -> bool;
      auto operator==(const BSTmap_iterator_const& rhs) -> bool;

      friend class BSTmap;
    };

    // BSTmap implementation
    Node* pRoot{nullptr};
    unsigned int size_{0};

    // end iterators are same for all BSTmaps, thus static
    // make BSTmap_iterator a friend
    // to allow BSTmap_iterator to access end iterators
    static BSTmap_iterator end_it;
    static BSTmap_iterator_const const_end_it;

  public:

    // Rule of 5
    BSTmap();
    BSTmap(const BSTmap& rhs);
    auto operator=(const BSTmap& rhs) -> BSTmap&;

    // TODO: Implement move stuff:
    // BSTmap(BSTmap &&rhs);
    // BSTmap &operator=(BSTmap &&rhs);

    virtual ~BSTmap();

    auto size() -> unsigned int;
    auto getdepth(Node*& node) const -> unsigned int;

    // value setter and getter
    auto operator[](const K& key) -> V&;

    // next method doesn't make sense
    // because operator[] inserts a non-existing element
    // which is not allowed on const maps
    // VALUE_TYPE operator[](int key) const;

    // BSTmap methods dealing with non-const iterator
    auto begin() -> iterator;
    auto end() -> iterator;
    auto find(const K& key) -> iterator;
    auto erase(iterator it) -> void;

    // BSTmap methods dealing with const iterator
    auto begin() const -> const_iterator;
    auto end() const -> const_iterator;
    auto find(const K& key) const -> const_iterator;
    // do not need this one (why) (because const functions should not be able to
    // edit the tree) BSTmap_iterator_const erase(BSTmap_iterator& it) const;

    // Checking methods
    auto sanityCheck() -> bool;

    // Printing methods
    auto get_edge_symbol(const Node* node) const -> char;
    auto print(std::ostream& os, bool print_value = false) const -> void;

    // inner class (BSTmap_iterator) doesn't have any special priveleges
    // in accessing private data/methods of the outer class (BSTmap)
    // so need friendship to allow BSTmap_iterator to access private
    // "BSTmap::end_it" BTW - same is true for outer class accessing inner class
    // private data
    friend struct BSTmap_iterator;
    friend struct BSTmap_iterator_const;

  private:

    // ...
  };

  // notice that it doesn't need to be friend
  template<typename KEY_TYPE, typename VALUE_TYPE>
  auto operator<<(std::ostream& os, const BSTmap<KEY_TYPE, VALUE_TYPE>& map)
    -> std::ostream&;
} // namespace CS280

#ifndef BST_CPP
  #include "bst-map.cpp"
#endif

#endif
