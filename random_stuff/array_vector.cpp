#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> numbers;
    
    // fill the array with values
    for(int i = 0; i <= 10; i++) {
        numbers.push_back(i);
    }

    // print the contents (values) of the array
    for(int number : numbers)
        cout << number << " ";
    cout << endl << endl;
        
    // it ... iterator  
    for(auto it = numbers.begin(); it != numbers.end(); it++) {
        cout << *it << endl;  // value of the element of the iterator
        cout << &it << endl;  // adress of the iterator
        cout << &(*it) << endl;  // adress of the element
    }
    cout << endl;
    // use .cbegin() and .cend() for constant iterators
    //  --> the values will be then unchangable in the loop
    

    // another usefull characteristics of vectors
    cout << "Size: " << numbers.size() << endl;
    numbers.resize(6);
    cout << "The changed size is: " << numbers.size() << endl;
    cout << "Max size: " << numbers.max_size() << endl;
    cout << "Number of free spaces: " << numbers.capacity() << endl;
    if (numbers.empty())
        cout << "Vector is empty" << endl;
    else
        cout << "Vector is not empty" << endl;
    cout << "Element [5] is: " << numbers[5] << endl;
    cout << "Element at(5) is: " << numbers.at(5) << endl;
    auto it = numbers.begin(); // using iterators
    cout << "The value of the 5th element is: " << *(it + 5) << endl;
    cout << "Front: " << numbers.front() << endl;
    cout << "Back: " << numbers.back() << endl;
    
    numbers.clear();
    
    return 0;
}
