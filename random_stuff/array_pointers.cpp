#include <iostream>

using namespace std;

int main()
{
    char* new_array = new char[4];
    
    for(int i = 0; i < 4; i++ ) {
        cout << "new_array[" << i << "]: ";
        cin >> new_array[i];
    }
    
    for(int i = 0; i < 3; i++ ) {
        cout << new_array[i] << ", ";
    }
    cout << new_array[3] << endl;
    
    for(int i = 0; i < 3; i++ ) {
        cout << "address of new_array[" << i << "]: " << (int*)(new_array + i) << endl;
    }
    cout << "address of new_array[" << 3 << "]: " << (int*)new_array + 3 << endl;
    cout << new_array << endl;
   
    return 0;
}
