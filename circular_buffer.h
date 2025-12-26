#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

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
        std::ifstream file(filename);

        file >> capacity >> size >> front >> back;

        data.resize(capacity);
        for (size_t i = 0; i < size; ++i) {
            size_t index = (front + i) % capacity;
            file >> data[index];
        }
    }

    void save(const std::string& filename) {
        std::ofstream file(filename);

        file << capacity << " " << size << " " << front << " " << back << "\n";

        for (size_t i = 0; i < size; ++i) {
            size_t index = (front + i) % capacity;
            file << data[index] << " ";
        }
    }
};

#endif // CIRCULAR_BUFFER_H