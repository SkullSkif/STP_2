#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>

class string {
private:
    static void* copy(void* dest, const void* src, size_t n) {
        char* d = static_cast<char*>(dest);
        const char* s = static_cast<const char*>(src);
        for (size_t i = 0; i < n; ++i) d[i] = s[i];
        return dest;
    }

    static size_t getlength(const char* str) {
        size_t len = 0;
        while (str[len] != '\0') ++len;
        return len;
    }

    static void* moving(void* dest, const void* src, size_t n) {
        char* d = static_cast<char*>(dest);
        const char* s = static_cast<const char*>(src);
        if (d == s) return dest;
        if (d < s) {
            for (size_t i = 0; i < n; ++i) d[i] = s[i];
        } else {
            for (size_t i = n; i > 0; --i) d[i - 1] = s[i - 1];
        }
        return dest;
    }

    static int compare(const void* ptr1, const void* ptr2, size_t n) {
        const unsigned char* p1 = static_cast<const unsigned char*>(ptr1);
        const unsigned char* p2 = static_cast<const unsigned char*>(ptr2);
        for (size_t i = 0; i < n; ++i) {
            if (p1[i] != p2[i]) return (p1[i] < p2[i]) ? -1 : 1;
        }
        return 0;
    }    
struct Buffer {
        char* data;
        size_t size;
        size_t capacity;
        int ref_count;

        Buffer(size_t cap = 15) : size(0), capacity(cap), ref_count(1) {
            data = new char[capacity + 1];
            data[0] = '\0';
        }

        Buffer(const char* str, size_t len) : size(len), capacity(len), ref_count(1) {
            data = new char[capacity + 1];
            string::copy(data, str, len);
            data[len] = '\0';
        }

        ~Buffer() {
            delete[] data;
        }

        void add_ref() { ++ref_count; }
        void release() { if (--ref_count == 0) delete this; }
        
        Buffer* detach() {
            if (ref_count > 1) {
                Buffer* new_buf = new Buffer(size);
                string::copy(new_buf->data, data, size);
                new_buf->size = size;
                new_buf->data[size] = '\0';
                release();
                return new_buf;
            }
            return this;
        }
    };

    Buffer* buf;

    void ensure_unique() {
        if (buf->ref_count > 1) {
            buf = buf->detach();
        }
    }

public:
    class iterator {
    private:
        char* ptr;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char*;
        using reference = char&;
        using iterator_category = std::random_access_iterator_tag;

        iterator(char* p = nullptr) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++ptr; return tmp; }
        iterator& operator--() { --ptr; return *this; }
        iterator operator--(int) { iterator tmp = *this; --ptr; return tmp; }

        iterator& operator+=(difference_type n) { ptr += n; return *this; }
        iterator& operator-=(difference_type n) { ptr -= n; return *this; }

        iterator operator+(difference_type n) const { return iterator(ptr + n); }
        iterator operator-(difference_type n) const { return iterator(ptr - n); }

        difference_type operator-(const iterator& other) const { return ptr - other.ptr; }

        reference operator[](difference_type n) const { return ptr[n]; }

        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
        bool operator<(const iterator& other) const { return ptr < other.ptr; }
        bool operator>(const iterator& other) const { return ptr > other.ptr; }
        bool operator<=(const iterator& other) const { return ptr <= other.ptr; }
        bool operator>=(const iterator& other) const { return ptr >= other.ptr; }
        
    };

    class const_iterator {
    private:
        const char* ptr;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = const char;
        using pointer = const char*;
        using reference = const char&;
        using iterator_category = std::random_access_iterator_tag;


        const_iterator(const char* p = nullptr) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        const_iterator& operator++() { ++ptr; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++ptr; return tmp; }
        const_iterator& operator--() { --ptr; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; --ptr; return tmp; }

        const_iterator& operator+=(difference_type n) { ptr += n; return *this; }
        const_iterator& operator-=(difference_type n) { ptr -= n; return *this; }

        const_iterator operator+(difference_type n) const { return const_iterator(ptr + n); }
        const_iterator operator-(difference_type n) const { return const_iterator(ptr - n); }

        difference_type operator-(const const_iterator& other) const { return ptr - other.ptr; }

        reference operator[](difference_type n) const { return ptr[n]; }

        bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }
        bool operator<(const const_iterator& other) const { return ptr < other.ptr; }
        bool operator>(const const_iterator& other) const { return ptr > other.ptr; }
        bool operator<=(const const_iterator& other) const { return ptr <= other.ptr; }
        bool operator>=(const const_iterator& other) const { return ptr >= other.ptr; }
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    string() : buf(new Buffer()) {}
    
    string(const char* str) {
        size_t len = string::getlength(str);
        buf = new Buffer(str, len);
    }
    
    string(const string& other) : buf(other.buf) {
        buf->add_ref();
    }
    
    string(string&& other) noexcept : buf(other.buf) {
        other.buf = new Buffer();
    }
    
    ~string() {
        buf->release();
    }

    string& operator=(const string& other) {
        if (this != &other) {
            buf->release();
            buf = other.buf;
            buf->add_ref();
        }
        return *this;
    }
    
    string& operator=(string&& other) noexcept {
        if (this != &other) {
            buf->release();
            buf = other.buf;
            other.buf = new Buffer();
        }
        return *this;
    }

    char& operator[](size_t pos) {
        ensure_unique();
        return buf->data[pos];
    }
    
    const char& operator[](size_t pos) const {
        return buf->data[pos];
    }

    char& at(size_t pos) {
        if (pos >= buf->size) {
            throw std::out_of_range("string::at");
        }
        ensure_unique();
        return buf->data[pos];
    }
    
    const char& at(size_t pos) const {
        if (pos >= buf->size) {
            throw std::out_of_range("string::at");
        }
        return buf->data[pos];
    }

    iterator begin() {
        ensure_unique();
        return iterator(buf->data);
    }
    
    const_iterator begin() const {
        return const_iterator(buf->data);
    }
    
    const_iterator cbegin() const {
        return const_iterator(buf->data);
    }

    iterator end() {
        ensure_unique();
        return iterator(buf->data + buf->size);
    }
    
    const_iterator end() const {
        return const_iterator(buf->data + buf->size);
    }
    
    const_iterator cend() const {
        return const_iterator(buf->data + buf->size);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }
    
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }
    
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(cend());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }
    
    const_reverse_iterator crend() const {
        return const_reverse_iterator(cbegin());
    }

    bool empty() const {
        return buf->size == 0;
    }

    size_t size() const {
        return buf->size;
    }
    
    size_t length() const {
        return buf->size;
    }

    size_t capacity() const {
        return buf->capacity;
    }

    void reserve(size_t new_cap) {
        if (new_cap > buf->capacity) {
            ensure_unique();
            Buffer* new_buf = new Buffer(new_cap);
            string::copy(new_buf->data, buf->data, buf->size);
            new_buf->size = buf->size;
            new_buf->data[buf->size] = '\0';
            buf->release();
            buf = new_buf;
        }
    }

void resize(size_t new_size, char ch = '\0') {
    ensure_unique();
    if (new_size > buf->capacity) {
        reserve(std::max(new_size, buf->capacity * 2));
    }
    
    if (new_size > buf->size) {
        std::fill(buf->data + buf->size, buf->data + new_size, ch);
    }
    buf->size = new_size;
    buf->data[new_size] = '\0'; 
}

void shrink_to_fit() {
    if (buf->size < buf->capacity) {
        ensure_unique();
        Buffer* new_buf = new Buffer(buf->size);
        string::copy(new_buf->data, buf->data, buf->size);
        new_buf->size = buf->size;
        new_buf->data[new_buf->size] = '\0';
        buf->release();
        buf = new_buf;
    }
}

    void clear() {
        ensure_unique();
        buf->size = 0;
        buf->data[0] = '\0';
    }

    iterator insert(const_iterator pos, char ch) {
        size_t offset = pos - cbegin();
        ensure_unique();
        
        if (buf->size + 1 > buf->capacity) {
            reserve(std::max(buf->size + 1, buf->capacity * 2));
        }
        
        string::moving(buf->data + offset + 1, buf->data + offset, buf->size - offset + 1);
        buf->data[offset] = ch;
        ++buf->size;
        
        return iterator(buf->data + offset);
    }

    void push_back(char ch) {
        insert(cend(), ch);
    }

    iterator erase(const_iterator pos) {
        return erase(pos, pos + 1);
    }

iterator erase(const_iterator first, const_iterator last) {
    size_t start = first - cbegin();
    size_t count = last - first;
    
    if (count > 0) {
        ensure_unique();
        string::moving(buf->data + start, buf->data + start + count, buf->size - start - count + 1);
        buf->size -= count;
        buf->data[buf->size] = '\0';
    }
    
    return iterator(buf->data + start);
}

    string& operator+=(char ch) {
        push_back(ch);
        return *this;
    }

    string& operator+=(const string& other) {
        if (other.buf->size > 0) {
            ensure_unique();
            if (buf->size + other.buf->size > buf->capacity) {
                reserve(buf->size + other.buf->size);
            }
            string::copy(buf->data + buf->size, other.buf->data, other.buf->size);
            buf->size += other.buf->size;
            buf->data[buf->size] = '\0';
        }
        return *this;
    }

    const char* c_str() const {
        return buf->data;
    }

    friend bool operator==(const string& lhs, const string& rhs) {
        return lhs.size() == rhs.size() && 
               string::compare(lhs.c_str(), rhs.c_str(), lhs.size()) == 0;
    }
    
    friend bool operator!=(const string& lhs, const string& rhs) {
        return !(lhs == rhs);
    }
};

string operator+(const string& lhs, const string& rhs) {
    string result = lhs;
    result += rhs;
    return result;
}

string operator+(const string& str, char ch) {
    string result = str;
    result += ch;
    return result;
}

string operator+(char ch, const string& str) {
    string result;
    result += ch;
    result += str;
    return result;
}