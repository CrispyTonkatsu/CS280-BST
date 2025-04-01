#include <random>
#include <algorithm>
#include "bst-map.h"
#include <iostream>
#include <vector>
#include <numeric>

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

int main() {
  int N = 100;
  CS280::BSTmap<int, int> map;
  std::vector<int> data(N); // data to insert
  std::iota(data.begin(), data.end(), 1);
  std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});

  simple_inserts(map, data);

  // now copy to constant map
  const CS280::BSTmap<int, int> map2(map);

  // sum up the copy
  CS280::BSTmap<int, int>::const_iterator it = map2.begin();
  CS280::BSTmap<int, int>::const_iterator it_e = map2.end();
  int total_keys = 0;
  int total_values = 0;
  for (; it != it_e; ++it) {
    total_keys += it->Key();
    total_values += it->Value();
  }
  std::cout << total_keys << std::endl;
  std::cout << total_values << std::endl;
}
