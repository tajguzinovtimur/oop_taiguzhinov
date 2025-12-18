#ifndef QUEUEITERATOR_H
#define QUEUEITERATOR_H

#include <iterator>
#include <cstddef>

// Предварительное объявление
template<typename T> class PmrQueue;

template<typename T>
class QueueIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    
private:
    // Используем Node из PmrQueue
    typename PmrQueue<T>::Node* current;

public:
    // Конструкторы
    QueueIterator() : current(nullptr) {}
    explicit QueueIterator(typename PmrQueue<T>::Node* node) : current(node) {}
    
    // Операторы
    QueueIterator& operator++() {
        if (current) {
            current = current->next;
        }
        return *this;
    }
    
    QueueIterator operator++(int) {
        QueueIterator temp = *this;
        ++(*this);
        return temp;
    }
    
    // Оператор разыменования
    reference operator*() {
        return current->data;
    }
    
    const reference operator*() const {
        return current->data;
    }
    
    // Оператор доступа к члену
    pointer operator->() {
        return &(current->data);
    }
    
    const pointer operator->() const {
        return &(current->data);
    }
    
    // Операторы сравнения
    bool operator==(const QueueIterator& other) const {
        return current == other.current;
    }
    
    bool operator!=(const QueueIterator& other) const {
        return !(*this == other);
    }
    
    // Преобразование в bool (для проверки валидности)
    explicit operator bool() const {
        return current != nullptr;
    }
};

#endif // QUEUEITERATOR_H