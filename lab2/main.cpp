#include <iostream>
#include <utility> 

template <typename T>
class UniquePtr {
public:

    explicit UniquePtr(T* ptr = nullptr) : ptr_(ptr) {}

    ~UniquePtr() {
        delete ptr_;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    T* get() {
        return ptr_;
    }

    void reset(T* p = nullptr) {
        delete ptr_;
        ptr_ = p;
    }

private:
    T* ptr_;
};

template <typename T>
class SharedPtr {
public:

    explicit SharedPtr(T* ptr = nullptr) : ptr_(ptr), count_(ptr ? new std::size_t(1) : nullptr) {}

    ~SharedPtr() {
        release();
    }

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), count_(other.count_) {
        if (count_) {
            ++(*count_);
        }
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            count_ = other.count_;
            if (count_) {
                ++(*count_);
            }
        }
        return *this;
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), count_(other.count_) {
        other.ptr_ = nullptr;
        other.count_ = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            count_ = other.count_;
            other.ptr_ = nullptr;
            other.count_ = nullptr;
        }
        return *this;
    }

    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    T* get() {
        return ptr_;
    }

    void reset(T* p = nullptr) {
        release();
        ptr_ = p;
        count_ = p ? new std::size_t(1) : nullptr;
    }

    std::size_t use_count() const {
        return count_ ? *count_ : 0;
    }

private:
    T* ptr_;
    std::size_t* count_;

    void release() {
        if (count_ && --(*count_) == 0) {
            delete count_;
            delete ptr_;
        }
    }
};

/*
int main() {
    UniquePtr<int> uptr(new int(42));
    std::cout << "UniquePtr value: " << *uptr << std::endl;

    SharedPtr<int> sptr1(new int(100));
    SharedPtr<int> sptr2(sptr1); // Копирование
    std::cout << "SharedPtr value: " << *sptr1 << ", use count: " << sptr1.use_count() << std::endl;

    sptr2.reset(new int(200)); // Сброс и создание нового объекта
    std::cout << "SharedPtr value after reset: " << *sptr1 << ", use count: " << sptr1.use_count() << std::endl;

    return 0;
}
*/