#include <iostream>
#include <memory>
#include <cstring>

class StringCow {
private:
    struct StringData {
        char* data;
        size_t length;

        StringData(const char* str) : length(strlen(str)) {
            data = new char[length + 1];
            strcpy(data, str);
        }

        ~StringData() {
            delete[] data;
        }
    };

    std::shared_ptr<StringData> pData;

    void detach() {
        if (!pData.unique()) {
            // Создаем копию данных, если shared_ptr не уникален
            pData = std::make_shared<StringData>(pData->data);
        }
    }

public:
    // Конструктор
    StringCow(const char* str = "") : pData(std::make_shared<StringData>(str)) {}

    // Конструктор копирования и оператор присваивания по умолчанию работают корректно с shared_ptr

    // Получение строки
    const char* c_str() const {
        return pData->data;
    }

    // Изменение символа с копированием по записи
    void setChar(size_t index, char ch) {
        if (index >= pData->length) return; // Проверка выхода за границы
        detach(); // Отделяем данные, если они разделены
        pData->data[index] = ch;
    }

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