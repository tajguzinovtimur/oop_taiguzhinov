#include "FixedBlockMemoryResource.h"
#include "PmrQueue.h"
#include <iostream>
#include <string>
#include <cassert>

struct ComplexType {
    int id;
    double value;
    std::string name;
    
    ComplexType(int i = 0, double v = 0.0, std::string n = "")
        : id(i), value(v), name(std::move(n)) {}
    
    friend std::ostream& operator<<(std::ostream& os, const ComplexType& obj) {
        os << "ComplexType{id=" << obj.id << ", value=" << obj.value 
           << ", name=\"" << obj.name << "\"}";
        return os;
    }
};

void test_int_queue() {
    std::cout << "\n=== Тест с int ===" << std::endl;
    
    FixedBlockMemoryResource mr(256, 32);
    PmrQueue<int> queue(&mr);
    
    for (int i = 1; i <= 5; ++i) {
        queue.push(i * 10);
    }
    
    std::cout << "Queue size after push: " << queue.size() << std::endl;
    assert(queue.size() == 5);
    
    std::cout << "Queue elements (using iterator): ";
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Queue elements (range-based for): ";
    for (const auto& elem : queue) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Front: " << queue.front() << std::endl;
    assert(queue.front() == 10);
    
    queue.pop();
    std::cout << "After pop, front: " << queue.front() << std::endl;
    assert(queue.front() == 20);
    
    for (int i = 6; i <= 8; ++i) {
        queue.push(i * 10);
    }
    
    std::cout << "Final queue size: " << queue.size() << std::endl;
    assert(queue.size() == 7);
    
    std::cout << "All elements: ";
    while (!queue.empty()) {
        std::cout << queue.front() << " ";
        queue.pop();
    }
    std::cout << std::endl;
    
    std::cout << "Int queue test passed!" << std::endl;
}

void test_complex_queue() {
    std::cout << "\n=== Тест с ComplexType ===" << std::endl;
    
    FixedBlockMemoryResource mr(512, 64);
    PmrQueue<ComplexType> queue(&mr);
    
    queue.push(ComplexType(1, 3.14, "Pi"));
    queue.emplace(2, 2.71, "Euler");
    queue.emplace(3, 1.41, "Sqrt2");
    
    std::cout << "Queue size: " << queue.size() << std::endl;
    assert(queue.size() == 3);
    
    std::cout << "Front: " << queue.front() << std::endl;
    assert(queue.front().id == 1);
    
    std::cout << "All complex elements:" << std::endl;
    int count = 0;
    for (const auto& elem : queue) {
        std::cout << "  " << elem << std::endl;
        ++count;
    }
    assert(count == 3);
    
    while (!queue.empty()) {
        std::cout << "Popping: " << queue.front() << std::endl;
        queue.pop();
    }
    
    std::cout << "Complex queue test passed!" << std::endl;
}

void test_memory_reuse() {
    std::cout << "\n=== Тест повторного использования памяти ===" << std::endl;
    
    FixedBlockMemoryResource mr(128, 32);
    PmrQueue<int> queue(&mr);
    
    std::cout << "Initial free blocks: " << mr.get_free_count() << std::endl;
    
    for (int i = 0; i < 3; ++i) {
        queue.push(i + 100);
    }
    
    std::cout << "After 3 pushes - allocated: " << mr.get_allocated_count() 
              << ", free: " << mr.get_free_count() << std::endl;
    
    while (!queue.empty()) {
        queue.pop();
    }
    
    std::cout << "After popping all - allocated: " << mr.get_allocated_count() 
              << ", free: " << mr.get_free_count() << std::endl;
    
    for (int i = 0; i < 3; ++i) {
        queue.push(i + 200);
    }
    
    std::cout << "After re-pushing - allocated: " << mr.get_allocated_count() 
              << ", free: " << mr.get_free_count() << std::endl;
    
    if (mr.get_free_count() == 0) {
        std::cout << "Memory reuse confirmed!" << std::endl;
    }
    
    std::cout << "Memory reuse test completed!" << std::endl;
}

void test_edge_cases() {
    std::cout << "\n=== Тест граничных случаев ===" << std::endl;
    
    FixedBlockMemoryResource mr(100, 32);
    PmrQueue<std::string> queue(&mr);
    
    assert(queue.empty());
    assert(queue.size() == 0);
    
    queue.push("Hello");
    assert(queue.size() == 1);
    assert(!queue.empty());
    assert(queue.front() == "Hello");
    
    queue.pop();
    assert(queue.empty());
    
    queue.push("World");
    PmrQueue<std::string> moved_queue = std::move(queue);
    assert(queue.empty());
    assert(moved_queue.size() == 1);
    assert(moved_queue.front() == "World");
    
    std::cout << "Edge cases test passed!" << std::endl;
}

int main() {
    std::cout << "=== Лабораторная работа №5: Очередь с Memory Resource Strategy 2 ===" << std::endl;
    std::cout << "=== Вариант 20: Queue + Fixed Block Memory with std::vector ===" << std::endl;
    
    try {
        test_int_queue();
        test_complex_queue();
        test_memory_reuse();
        test_edge_cases();
        
        std::cout << "\n=== Все тесты успешно пройдены! ===" << std::endl;
        
        std::cout << "\n=== Демонстрация работы ===" << std::endl;
        {
            FixedBlockMemoryResource demo_mr(1024, 64);
            PmrQueue<int> demo_queue(&demo_mr);
            
            std::cout << "Adding numbers 1-10..." << std::endl;
            for (int i = 1; i <= 10; ++i) {
                demo_queue.push(i);
            }
            
            std::cout << "Queue contains: ";
            for (const auto& num : demo_queue) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
            
            std::cout << "Removing first 5 elements..." << std::endl;
            for (int i = 0; i < 5; ++i) {
                demo_queue.pop();
            }
            
            std::cout << "Now queue contains: ";
            for (const auto& num : demo_queue) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "\n=== Программа завершена успешно ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}