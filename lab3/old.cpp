#include <iostream>
#include <iterator>
#include <algorithm>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t list_size;

public:
    class Iterator {
    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() { return current->data; }
        T* operator->() { return &current->data; }

        // Префиксный инкремент
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        // Постфиксный инкремент
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        // Префиксный декремент
        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        // Постфиксный декремент
        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator!=(const Iterator& other) const { return current != other.current; }
        bool operator==(const Iterator& other) const { return current == other.current; }

    private:
        Node* current;
    };

    LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

    template <typename It>
    LinkedList(It begin, It end) : head(nullptr), tail(nullptr), list_size(0) {
        for (auto it = begin; it != end; ++it) {
            push_back(*it);
        }
    }

    ~LinkedList() { clear(); }

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++list_size;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        ++list_size;
    }

    T& front() { return head->data; }
    T& back() { return tail->data; }

    bool empty() const { return list_size == 0; }
    
    size_t size() const { return list_size; }

    void clear() {
        while (!empty()) {
            Node* temp = head;
            head = head->next;
            delete temp;
            --list_size;
        }
        head = tail = nullptr;
    }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    
    // Константные итераторы
    class ConstIterator {
    public:
        ConstIterator(Node* node) : current(node) {}

        const T& operator*() const { return current->data; }
        
        ConstIterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const ConstIterator& other) const { return current != other.current; }
        
    private:
         Node* current; 
     };

     ConstIterator cbegin() const { return ConstIterator(head); }
     ConstIterator cend() const { return ConstIterator(nullptr); }

     // Обратные итераторы
     class ReverseIterator {
     public:
         ReverseIterator(Node* node) : current(node) {}

         T& operator*() { return current->data; }

         ReverseIterator& operator++() {
             current = current->prev;
             return *this;
         }

         bool operator!=(const ReverseIterator& other) const { return current != other.current; }
         
     private:
         Node* current; 
     };

     ReverseIterator rbegin() { return ReverseIterator(tail); }
     ReverseIterator rend() { return ReverseIterator(nullptr); }

     // Константные обратные итераторы
     class ConstReverseIterator {
     public:
         ConstReverseIterator(Node* node) : current(node) {}

         const T& operator*() const { return current->data; }

         ConstReverseIterator& operator++() {
             current = current->prev;
             return *this;
         }

         bool operator!=(const ConstReverseIterator& other) const { return current != other.current; }
         
     private:
         Node* current; 
     };

     ConstReverseIterator crbegin() const { return ConstReverseIterator(tail); }
     ConstReverseIterator crend() const { return ConstReverseIterator(nullptr); }
};

int main() {
   LinkedList<int> list;

   // Добавление элементов
   list.push_back(3);
   list.push_back(1);
   list.push_back(4);
   list.push_back(2);

   std::cout << "Original List: ";
   for (auto it = list.begin(); it != list.end(); ++it)
       std::cout << *it << " ";
   std::cout << std::endl;

   // Использование std::find
   auto it_find = std::find(list.begin(), list.end(), 2);
   if (it_find != list.end())
       std::cout << "Found: " << *it_find << std::endl;

   // Использование std::reverse
   std::reverse(list.begin(), list.end());
   std::cout << "Reversed List: ";
   for (auto it = list.begin(); it != list.end(); ++it)
       std::cout << *it << " ";
   std::cout << std::endl;

   // Использование std::sort
   std::sort(list.begin(), list.end());
   std::cout << "Sorted List: ";
   for (auto it = list.begin(); it != list.end(); ++it)
       std::cout << *it << " ";
   std::cout << std::endl;

   // Проверка front и back
   std::cout << "Front: " << list.front() << ", Back: " << list.back() << std::endl;

   // Очистка списка
   list.clear();
   
   if (list.empty())
       std::cout << "List is empty after clear." << std::endl;

   return 0;
}