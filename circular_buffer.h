#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <fstream>

template<typename T>
class CircularBuffer {
private:
    std::vector<T> data;
    size_t front = 0;
    size_t back = 0;
    size_t size = 0;
    size_t capacity;

public:
    CircularBuffer(size_t cap) : capacity(cap) {
        data.resize(cap);
    }

    void push(const T& value) {
        if (full()) throw std::runtime_error("Full");
        data[back] = value;
        back = (back + 1) % capacity;
        ++size;
    }

    T pop() {
        if (empty()) throw std::runtime_error("Empty");
        T value = data[front];
        front = (front + 1) % capacity;
        --size;
        return value;
    }

    bool empty() { return size == 0; }
    bool full() { return size == capacity; }
    size_t get_size() { return size; }
    size_t get_capacity() { return capacity; }

    void load(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) throw std::runtime_error("Cannot open file");

        file.read((char*)&capacity, sizeof(capacity));
        file.read((char*)&size, sizeof(size));
        file.read((char*)&front, sizeof(front));
        file.read((char*)&back, sizeof(back));

        data.resize(capacity);
        for (size_t i = 0; i < size; ++i) {
            size_t index = (front + i) % capacity;
            file.read((char*)&data[index], sizeof(T));
        }
    }

    void save(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) throw std::runtime_error("Cannot create file");

        file.write((const char*)&capacity, sizeof(capacity));
        file.write((const char*)&size, sizeof(size));
        file.write((const char*)&front, sizeof(front));
        file.write((const char*)&back, sizeof(back));

        for (size_t i = 0; i < size; ++i) {
            size_t index = (front + i) % capacity;
            file.write((const char*)&data[index], sizeof(T));
        }
    }
};

#endif // CIRCULAR_BUFFER_H