#ifndef BSTMAP_H
#define BSTMAP_H

#include <iosfwd>
#include <optional>

namespace CS280 {

  /**
   * @brief This class represents a binary search tree using key K and stores
   * values of type V. It has support for the following operations:
   * - Insert
   * - Find
   * - Erase
   *
   * @param K The type for the key to be used (Needs the < and > operator
   * overloads)
   * @param V The type for the values to be used (Needs to be copiable)
   */
  template<typename K, typename V>
  class BSTmap {

    // Forward declarations for the struct
    struct BSTmap_iterator;
    struct BSTmap_iterator_const;

  public:

    // standard names for iterator types
    typedef BSTmap_iterator iterator;
    typedef BSTmap_iterator_const const_iterator;

    /**
     * @brief This class represents a Node in the BST. It mainly features
     * getters, setters and traversal methods.
     */
    class Node {
    public:

      /**
       * @brief Factory method for an empty unlinked node of key K.
       *
       * @param key The key to use.
       * @return Pointer to allocated node.
       */
      static auto CreateNode(K key) -> Node*;

      /**
       * @brief Constructor for a Node.
       *
       * @param k The key of this node.
       * @param v The value of this node.
       * @param h The node's height.
       * @param b The node's balance.
       * @param l The left child's pointer.
       * @param r The right child's pointer.
       */
      Node(K k, V val, Node* p, int h, int b, Node* l, Node* r);

      // Deleted copy constructor
      Node(const Node&) = delete;

      // Deleted copy assignment operator
      auto operator=(const Node&) -> Node& = delete;

      /**
       * @brief Getter of a reference to the key of this node.
       * @return Const reference to the key.
       */
      auto Key() const -> const K&; // return a const reference

      /**
       * @brief Getter of a reference to the value of this node.
       * @return Reference to the value.
       */
      auto Value() -> V&; // return a reference

      /**
       * @brief Function to get the node furthest left of a node.
       * @return Pointer to the node.
       */
      auto first() -> Node*; // minimum - follow left as far as possible

      /**
       * @brief Function to get the node furthest right of a node.
       * @return Pointer to the node.
       */
      auto last() -> Node*; // maximum - follow right as far as possible

      /**
       * @brief Will get the node's successor
       * @return Pointer to the node.
       */
      auto increment() -> Node*; // successor

      /**
       * @brief Will get the node's predecessor
       * @return Pointer to the node.
       */
      auto decrement() -> Node*; // predecessor

      /**
       * @brief Prints a node
       */
      auto print(std::ostream& os) const -> void;

    private:

      /**
       * @brief Returns whether this node is the right child of a node.
       * @return Whether it is the right child.
       */
      auto is_right_child() const -> bool;

      /**
       * @brief Returns whether this node is the left child of a node.
       * @return Whether it is the left child.
       */
      auto is_left_child() const -> bool;

      /**
       * @brief Will add a child updating the links properly and setting it to
       * the correct side.
       */
      auto add_child(Node& node) -> void;

      /**
       * @brief Returns whether the node has children or not.
       * @return Whether the node has children.
       */
      auto has_children() const -> bool;

      /**
       * @brief Gets the only child this node has.
       * @return Optional pointer to the node. If there are 2 children nodes it
       * returns nullopt.
       */
      auto get_only_child() -> std::optional<Node*>;

      /**
       * @brief The key of this node.
       */
      K key;

      /**
       * @brief The value that is being held by the node.
       */
      V value;

      // NOTE: Actually use the values for the AVL assignment
      int height, balance; // optional

      /**
       * @brief The parent of this node
       */
      Node* parent;

      /**
       * @brief The left child's pointer
       */
      Node* left;

      /**
       * @brief The right child's pointer
       */
      Node* right;

      // Friending the BSTmap class so the internals can be accessed.
      friend class BSTmap;
    };

  private:

    struct BSTmap_iterator {
    private:

      Node* p_node;

    public:

      BSTmap_iterator(Node* p = nullptr);
      BSTmap_iterator(BSTmap_iterator& rhs);
      auto operator=(const BSTmap_iterator& rhs) -> BSTmap_iterator&;
      auto operator++() -> BSTmap_iterator&;
      auto operator++(int) -> BSTmap_iterator;
      auto operator--() -> BSTmap_iterator&;
      auto operator--(int) -> BSTmap_iterator;
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
      BSTmap_iterator_const(BSTmap_iterator_const& rhs);
      auto operator=(const BSTmap_iterator_const& rhs)
        -> BSTmap_iterator_const&;
      auto operator++() -> BSTmap_iterator_const&;
      auto operator++(int) -> BSTmap_iterator_const;
      auto operator--() -> BSTmap_iterator_const&;
      auto operator--(int) -> BSTmap_iterator_const;
      auto operator*() -> const Node&;
      auto operator->() -> const Node*;
      auto operator!=(const BSTmap_iterator_const& rhs) -> bool;
      auto operator==(const BSTmap_iterator_const& rhs) -> bool;

      friend class BSTmap;
    };

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

    BSTmap(BSTmap&& rhs);
    BSTmap& operator=(BSTmap&& rhs);

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

    // Alias for type that will be used a lot
    struct NodeSearch {
      Node& node;
      std::size_t depth;
    };

    auto search_node(K key) const -> std::optional<NodeSearch>;
    auto clear() -> void;

    Node* root{nullptr};
    unsigned int size_{0};
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
