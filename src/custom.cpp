#include <algorithm>
#include <numeric>
#include <random>
#include <utility>
#include "bst-map.h"

void simple_inserts(
  CS280::BSTmap<int, int>& map,
  const std::vector<int>& data
) {
  // insert (using index operator) and perform sanity check each time
  for (const int& key: data) {
    map[key] = key * key; // value is not important
    // if you have the method below, uncomment next line
    if (!map.sanityCheck()) {
      std::cout << "Error\n";
    }
  }
}

void test_move_contructor() {
  int N = 1000;
  CS280::BSTmap<int, int> map;
  std::vector<int> data(N); // data to insert
  std::iota(data.begin(), data.end(), 1);
  std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});

  // insert some number of elements between N/2 and N
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<unsigned int> dis(N / 2, N);
  data.resize(dis(gen));
  simple_inserts(map, data);

  // now copy the map
  CS280::BSTmap<int, int> map2(std::move(map));

  // traverse original, find in copy (should find all values)
  CS280::BSTmap<int, int>::iterator it = map.begin();
  CS280::BSTmap<int, int>::iterator it_e = map.end();
  for (; it != it_e; ++it) {
    if (map2.find(it->Key()) == map2.end()) {
      std::cout << "Not found in a copy\n";
    }
  }

  // traverse copy, find in original (shouldn't be there no more)
  CS280::BSTmap<int, int>::iterator it2 = map2.begin();
  CS280::BSTmap<int, int>::iterator it2_e = map2.end();
  for (; it2 != it2_e; ++it2) {
    if (map.find(it2->Key()) != map.end()) {
      std::cout << "Found in a original\n";
    }
  }
}

void test_move_assign() {
  // random map
  int N = 1000;
  CS280::BSTmap<int, int> map;
  std::vector<int> data(N); // data to insert
  std::iota(data.begin(), data.end(), 1);
  std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});

  // insert some number of elements between N/2 and N
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<unsigned int> dis(N / 2, N);
  data.resize(dis(gen));
  simple_inserts(map, data);

  // random map2
  CS280::BSTmap<int, int> map2;
  std::vector<int> data2(N); // data to insert
  std::iota(data2.begin(), data2.end(), 1);
  std::shuffle(
    data2.begin(),
    data2.end(),
    std::mt19937{std::random_device{}()}
  );

  // insert some number of elements between N/2 and N
  data2.resize(dis(gen));
  simple_inserts(map2, data2);

  // now assign
  map2 = std::move(map);

  // traverse original, find in copy
  CS280::BSTmap<int, int>::iterator it = map.begin();
  CS280::BSTmap<int, int>::iterator it_e = map.end();
  for (; it != it_e; ++it) {
    if (map2.find(it->Key()) == map2.end()) {
      std::cout << "Not found in a assigned\n";
    }
  }

  // traverse copy, find in original (shouldn't be there no more)
  CS280::BSTmap<int, int>::iterator it2 = map2.begin();
  CS280::BSTmap<int, int>::iterator it2_e = map2.end();
  for (; it2 != it2_e; ++it2) {
    if (map.find(it2->Key()) != map.end()) {
      std::cout << "Found in a original\n";
    }
  }
}

int main() { 
  test_move_contructor(); 
  test_move_assign();
}
