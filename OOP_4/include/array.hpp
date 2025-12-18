#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <memory>
#include <iostream>
#include <stdexcept>
#include <utility>

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t capacity;
    size_t size;
    
    void resize(size_t newCapacity) {
        std::unique_ptr<T[]> newData = std::make_unique<T[]>(newCapacity);
        
        // Перемещаем элементы
        for (size_t i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]);
        }
        
        data = std::move(newData);
        capacity = newCapacity;
    }
    
public:
    Array() : data(nullptr), capacity(0), size(0) {}
    
    explicit Array(size_t initialCapacity) 
        : data(std::make_unique<T[]>(initialCapacity)), 
          capacity(initialCapacity), 
          size(0) {}
    
    // Копирование
    Array(const Array& other) 
        : data(std::make_unique<T[]>(other.capacity)),
          capacity(other.capacity),
          size(other.size) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];  // Здесь будет вызываться оператор копирования T
        }
    }
    
    // Перемещение
    Array(Array&& other) noexcept 
        : data(std::move(other.data)),
          capacity(other.capacity),
          size(other.size) {
        other.capacity = 0;
        other.size = 0;
    }
    
    ~Array() = default;
    
    // Оператор присваивания копированием
    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other);
            swap(temp);
        }
        return *this;
    }
    
    // Оператор присваивания перемещением
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            capacity = other.capacity;
            size = other.size;
            
            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }
    
    void swap(Array& other) noexcept {
        std::swap(data, other.data);
        std::swap(capacity, other.capacity);
        std::swap(size, other.size);
    }
    
    // Добавление элемента
    void push_back(const T& value) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }
    
    // Добавление элемента с перемещением
    void push_back(T&& value) {
        if (size >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = std::move(value);
    }
    
    // Удаление элемента по индексу
    void remove(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        // Сдвигаем элементы
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }
    
    // Доступ к элементу
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // Размер массива
    size_t getSize() const { return size; }
    
    // Емкость массива
    size_t getCapacity() const { return capacity; }
    
    // Очистка массива
    void clear() {
        data.reset();
        capacity = 0;
        size = 0;
    }
    
    // Итераторы (простая реализация)
    T* begin() { return data.get(); }
    const T* begin() const { return data.get(); }
    T* end() { return data.get() + size; }
    const T* end() const { return data.get() + size; }
};

#endif // ARRAY_HPP