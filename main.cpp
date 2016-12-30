#include <iostream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <tuple>

using jug = std::pair<int,int>;

namespace std {
  std::ostream & operator<<(std::ostream & os, const jug & j) {
    os << "(" << j.first << "," << j.second << ")";
    return os;
  }
}

class solution {
public:
  bool canMeasureWater(int x, int y, int z) {
    auto paths = getPaths(std::make_tuple(x,y,z), std::vector<jug>{std::make_pair(0,0)});
    std::for_each(paths.begin(), paths.end(),
		  [](const std::vector<jug> & path){
		    std::copy(path.begin(), path.end(), std::ostream_iterator<jug>(std::cout, ""));
		    std::cout << std::endl;
		  });
    return !paths.empty();
  }

private:
  std::vector<std::vector<jug>> getPaths(const std::tuple<int,int,int> & t, const std::vector<jug> & curr) {
    std::vector<std::vector<jug>> result;
    if (curr.back().first == std::get<2>(t) || curr.back().second == std::get<2>(t))
      result.push_back(curr);
    else {
      std::vector<jug> next = getNext(t,curr);
      for (auto nx : next) {
	auto cpy = curr;
	cpy.push_back(nx);
	auto temp = getPaths(t,cpy);
	std::copy(temp.begin(), temp.end(), std::inserter(result,result.end()));
      }
    }
    return result;
  }

  std::vector<jug> getNext(const std::tuple<int,int,int> & t, const std::vector<jug> & curr) {
    std::vector<jug> next;
    if (curr.back().first == std::get<0>(t) && curr.back().second == std::get<1>(t)) {
      next.push_back(std::make_pair(0, curr.back().second));
      next.push_back(std::make_pair(curr.back().first, 0));
    }
    else {
      next.push_back(std::make_pair(std::get<0>(t), curr.back().second));
      next.push_back(std::make_pair(curr.back().first, 0));
      if (curr.back().second >= std::get<0>(t)-curr.back().first)
	next.push_back(std::make_pair(std::get<0>(t), curr.back().second-std::get<0>(t)+curr.back().first));
      else
	next.push_back(std::make_pair(curr.back().first+curr.back().second,0));

      next.push_back(std::make_pair(curr.back().first, std::get<1>(t)));
      next.push_back(std::make_pair(0, curr.back().second));
      if (curr.back().first >= std::get<1>(t)-curr.back().second)
	next.push_back(std::make_pair(curr.back().first-std::get<1>(t)+curr.back().second, std::get<1>(t)));
      else
	next.push_back(std::make_pair(0, curr.back().first+curr.back().second));
    }

    auto it = next.begin();
    while (it != next.end()) {
      if (std::find(curr.begin(), curr.end(), *it) != curr.end())
	it = next.erase(it);
      else
	++it;
    }
    return next;
  }
};

int main() {
  // int x{3}, y{5}, z{4};
  int x = 2, y = 6, z = 5;

  solution soln;
  bool canBeMeasured = soln.canMeasureWater(x,y,z);
  if (canBeMeasured)
    std::cout << z << " liters of water can be measured from jugs of " << x << " and " << y << " liters!\n";
  else
    std::cout << z << " liters of water CANNOT be measured from jugs of " << x << " and " << y << " liters!\n";
}
