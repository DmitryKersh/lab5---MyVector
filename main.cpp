#include "MyVector.h"
#include "iostream"
#include <string>

using std::cout;

class CustomStruct {
  std::string text;
  int number;

public:
  CustomStruct(std::string text, int number) : text(text), number(number) {}
  CustomStruct() : CustomStruct("default text", 1) {}
  friend std::ostream& operator<<(std::ostream& out, CustomStruct const& item){
    out << item.text << " - " << item.number;
  }
};

int main(){

  MyVector<int> ints({2, 43, 1, 18});

  ints.pop_back();
  ints.pop_back();

  cout << ints; // 2, 43

  ints.push_back(13);
  ints[1] = 34;

  cout << ints; // 2, 34, 13

  ints.resize(6);
  ints.erase(1); // 2, 13, 0, 0, 0

  MyVector<int> ints_2(ints);
  cout << ints_2; // 2, 13, 0, 0, 0
  cout << ints_2.size() << ' ' << ints_2.capacity() << endl; // 5 6

  ints_2.at(3) = 8;
  ints_2.back() = 9;
  ints_2.front() = 5;

  cout << ints_2; // 5, 13, 0, 8, 9

  ints_2.reserve(10);
  cout << ints_2.size() << ' ' << ints_2.capacity() << endl; // 5 10

  ints_2.reserve(1); // should do nothing
  cout << ints_2.size() << ' ' << ints_2.capacity() << endl; // 5 10

  cout << std::boolalpha << (ints.data() == &(ints[0])) << endl; // true

  ints.swap(ints_2);
  cout << ints; // 5, 13, 0, 8, 9

  ints.clear();
  cout << ints; // <empty>

  for (int i = 0; i < 15; i++){
    ints.push_back(i*i);
    cout << "Number: " << i
         << "; Size: " << ints.size()
         << "; Capacity: " << ints.capacity() << endl;
  }
  /*
   * У вас таблица неправильная, если округлять в меньшую,
   * то длина 1 так и останется, а если в большую, то с 3
   * расширится до 5 -> 8 -> 12 -> 18 -> ...
   *
   * Number: 0; Size: 1; Capacity: 1
   * Number: 1; Size: 2; Capacity: 2
   * Number: 2; Size: 3; Capacity: 3
   * Number: 3; Size: 4; Capacity: 5
   * Number: 4; Size: 5; Capacity: 5
   * Number: 5; Size: 6; Capacity: 8
   * Number: 6; Size: 7; Capacity: 8
   * Number: 7; Size: 8; Capacity: 8
   * Number: 8; Size: 9; Capacity: 12
   * Number: 9; Size: 10; Capacity: 12
   * Number: 10; Size: 11; Capacity: 12
   * Number: 11; Size: 12; Capacity: 12
   * Number: 12; Size: 13; Capacity: 18
   * Number: 13; Size: 14; Capacity: 18
   * Number: 14; Size: 15; Capacity: 18
   */

  // for CustomStruct:

  MyVector<CustomStruct> cs({{"one", 1},
                                    {"three", 3},
                                    {"six", 6}});

  cout << cs; // one - 1, three - 3, six - 6

  cs.insert(1, {"thousand", 1000});
  cs.push_back({"10000e", 271828});

  cout << cs;

  cs.resize(8);
  cs.back() = cs.front();
  //one - 1, thousand - 1000, three - 3, six - 6, 10000e - 271828, default text - 1, default text - 1, one - 1
  cout << cs;

  cout << std::boolalpha << (cs.data() == &(cs[0])) << endl; // true
  cs.clear();
  cout << cs;

  return 0;
}