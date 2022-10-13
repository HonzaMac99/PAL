#include <iostream>

using namespace std;

int main()
{
    char* new_char_array = new char[4];
    
    for(int i = 0; i < 4; i++ ) {
        cout << "new_char_array[" << i << "]: ";
        cin >> new_char_array[i];
    }
    
    for(int i = 0; i < 3; i++ ) {
        cout << new_char_array[i] << ", ";
    }
    cout << new_char_array[3] << endl;
    
    for(int i = 0; i < 3; i++ ) {
        cout << "address of new_char_array[" << i << "]:        " << (int*)(new_char_array + i) << endl;
    }
    cout << "address of (int*)new_char_array[" << 3 << "]:  " << (int*)new_char_array + 3 << endl;
    cout << new_char_array << endl;
    
    delete [] new_char_array;
    new_char_array = NULL;
   
    return 0;
}
