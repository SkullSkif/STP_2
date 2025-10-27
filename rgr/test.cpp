#include <iostream>
#include <cstring>

class StringCow {
private:
    struct StringData {
        char* data;
        size_t refCount;

        StringData(const char* str) : refCount(1) {
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        }

        ~StringData() {
            delete[] data;
        }
    };

    StringData* pData;

    void detach() {
        if (pData->refCount > 1) {
            // Create own copy if shared
            StringData* newData = new StringData(pData->data);
            --pData->refCount;
            pData = newData;
        }
    }

public:
    // Constructor
    StringCow(const char* str = "") {
        pData = new StringData(str);
    }

    // Copy constructor
    StringCow(const StringCow& other) {
        pData = other.pData;
        ++pData->refCount;
    }

    // Assignment operator
    StringCow& operator=(const StringCow& other) {
        if (this != &other) {
            if (--pData->refCount == 0) {
                delete pData;
            }
            pData = other.pData;
            ++pData->refCount;
        }
        return *this;
    }

    // Destructor
    ~StringCow() {
        if (--pData->refCount == 0) {
            delete pData;
        }
    }

    // Accessor
    const char* c_str() const {
        return pData->data;
    }

    // Write operation example: modify character at index
    void setChar(size_t index, char ch) {
        if (index >= strlen(pData->data)) return; // Out of bounds check

        detach(); // Ensure unique before modifying
        pData->data[index] = ch;
    }

    // Print string
    void print() const {
        std::cout << pData->data << std::endl;
    }
};


int main(){
    StringCow str1("TEST");
    // std::cout << str1.c_str() << '\n';
    printf("%x: %s\n", str1.c_str(), str1.c_str());
    StringCow str2(str1);
    printf("%x: %s\n", str2.c_str(), str2.c_str());
    str2.setChar(1, 'O');
    printf("%x: %s\n", str2.c_str(), str2.c_str());
    printf("%x: %s\n", str1.c_str(), str1.c_str());


    // printf("%x\n", str2.c_str());
    // str2.setChar(0, '1');
    // printf("%x\n", str2.c_str());



    // std::cout << str2.c_str();

    return 0;
}