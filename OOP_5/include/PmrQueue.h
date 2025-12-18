#ifndef PMRQUEUE_H
#define PMRQUEUE_H

#include "QueueIterator.h"
#include <memory_resource>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template<typename T>
class PmrQueue {
public:
    // Объявляем Node публично, чтобы QueueIterator мог его использовать
    struct Node {
        T data;
        Node* next;
        
        // Исправленный конструктор
        template<typename... Args>
        Node(Node* nxt, Args&&... args) 
            : next(nxt), data(std::forward<Args>(args)...) {}
    };
    
    using iterator = QueueIterator<T>;
    using const_iterator = QueueIterator<const T>;
    
    // Дружественное объявление для доступа к Node
    friend class QueueIterator<T>;
    friend class QueueIterator<const T>;
    
private:
    Node* head;
    Node* tail;
    std::size_t count;
    std::pmr::polymorphic_allocator<Node> allocator;

public:
    // Конструкторы
    explicit PmrQueue(std::pmr::memory_resource* mr = std::pmr::get_default_resource())
        : head(nullptr), tail(nullptr), count(0), allocator(mr) 
    {
        std::cout << "PmrQueue created with memory_resource: " << mr << std::endl;
    }
    
    ~PmrQueue() { clear(); }
    
    // Запрет копирования
    PmrQueue(const PmrQueue&) = delete;
    PmrQueue& operator=(const PmrQueue&) = delete;
    
    // Перемещение
    PmrQueue(PmrQueue&& other) noexcept
        : head(other.head), tail(other.tail), count(other.count), allocator(std::move(other.allocator)) 
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }
    
    PmrQueue& operator=(PmrQueue&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            count = other.count;
            allocator = std::move(other.allocator);
            
            other.head = nullptr;
            other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }
    
    // Основные операции
    void push(const T& value) {
        Node* new_node = allocator.allocate(1);
        try {
            // Исправленный вызов конструктора
            allocator.construct(new_node, nullptr, value);
        } catch (...) {
            allocator.deallocate(new_node, 1);
            throw;
        }
        
        if (tail) {
            tail->next = new_node;
            tail = new_node;
        } else {
            head = tail = new_node;
        }
        ++count;
        
        std::cout << "Pushed value: " << value << std::endl;
    }
    
    template<typename... Args>
    void emplace(Args&&... args) {
        Node* new_node = allocator.allocate(1);
        try {
            // Исправленный вызов конструктора
            allocator.construct(new_node, nullptr, std::forward<Args>(args)...);
        } catch (...) {
            allocator.deallocate(new_node, 1);
            throw;
        }
        
        if (tail) {
            tail->next = new_node;
            tail = new_node;
        } else {
            head = tail = new_node;
        }
        ++count;
        
        std::cout << "Emplaced value" << std::endl;
    }
    
    void pop() {
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }
        
        Node* to_delete = head;
        head = head->next;
        
        if (!head) {
            tail = nullptr;
        }
        
        std::cout << "Popped value: " << to_delete->data << std::endl;
        
        allocator.destroy(to_delete);
        allocator.deallocate(to_delete, 1);
        --count;
    }
    
    T& front() {
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }
        return head->data;
    }
    
    const T& front() const {
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }
        return head->data;
    }
    
    bool empty() const {
        return count == 0;
    }
    
    std::size_t size() const {
        return count;
    }
    
    // Очистка очереди
    void clear() {
        while (!empty()) {
            pop();
        }
    }
    
    // Итераторы
    iterator begin() {
        return iterator(head);
    }
    
    iterator end() {
        return iterator(nullptr);
    }
    
    const_iterator begin() const {
        return const_iterator(const_cast<Node*>(head));
    }
    
    const_iterator end() const {
        return const_iterator(nullptr);
    }
    
    // Информация
    void print_stats() const {
        std::cout << "Queue size: " << count 
                  << ", empty: " << (empty() ? "yes" : "no") 
                  << std::endl;
    }
};

#endif // PMRQUEUE_H