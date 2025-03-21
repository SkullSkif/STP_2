#include <cstddef> // для std::size_t

template<typename T>
class UniquePtr {
private:
    T* ptr; // Указатель на ресурс

public:
    // Конструктор
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    // Деструктор
    ~UniquePtr() {
        delete ptr;
    }

    // Запрет копирования
    UniquePtr(const UniquePtr&) = delete; // Конструктор копирования
    UniquePtr& operator=(const UniquePtr&) = delete; // Оператор присваивания

    // Перемещение
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr; // Освобождаем старый указатель
            ptr = other.ptr; // Перемещаем указатель
            other.ptr = nullptr;
        }
        return *this;
    }

    // Операторы разыменования
    T& operator*() {
        return *ptr; // Разыменование указателя
    }

    T* operator->() {
        return ptr; // Доступ к членам через указатель
    }

    // Получение сырого указателя
    T* get() const {
        return ptr; // Возвращаем сырой указатель
    }

    // Сброс указателя
    void reset(T* p = nullptr) {
        delete ptr; // Освобождаем текущий указатель
        ptr = p; // Присваиваем новый указатель
    }
};

template<typename T>
class SharedPtr {
private:
    T* ptr; // Указатель на ресурс
    std::size_t* count; // Счетчик ссылок

public:
    // Конструктор
    explicit SharedPtr(T* p = nullptr) : ptr(p), count(new std::size_t(1)) {}

    // Деструктор
    ~SharedPtr() {
        release(); // Освобождаем ресурсы при разрушении
    }

    // Копирующий конструктор
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), count(other.count) {
        ++(*count); // Увеличиваем счетчик
    }

    // Оператор присваивания
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release(); // Освобождаем старый ресурс
            ptr = other.ptr;
            count = other.count;
            ++(*count); // Увеличиваем счетчик
        }
        return *this;
    }

    // Перемещение
    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), count(other.count) {
        other.ptr = nullptr; 
        other.count = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            count = other.count;
            other.ptr = nullptr;
            other.count = nullptr;
        }
        return *this;
    }

    // Операторы разыменования
    T& operator*() {
        return *ptr; // Разыменование указателя
    }

    T* operator->() {
        return ptr; // Доступ к членам через указатель
    }

    // Получение сырого указателя
    T* get() const {
        return ptr; // Возвращаем сырой указатель
    }

    // Сброс указателя
    void reset(T* p = nullptr) {
        release();
        ptr = p;
        count = new std::size_t(1); // Обновляем счетчик
    }

    // Получение счетчика
    std::size_t use_count() const {
        return *count; // Возвращаем текущее значение счетчика
    }

private:
    // Освобождение ресурсов
    void release() {
        if (count && --(*count) == 0) {
            delete ptr; // Освобождаем ресурс
            delete count; // Освобождаем счетчик
        }
    }
};