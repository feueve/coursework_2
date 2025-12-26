#include <iostream>
#include "circular_buffer.h"

int main() {
    CircularBuffer<int> buffer(3);

    std::cout << "Adding 10, 20, 30\n";
    buffer.push(10);
    buffer.push(20);
    buffer.push(30);

    std::cout << "Buffer full: " << (buffer.full() ? "yes" : "no") << "\n";

    buffer.save("buffer.bin");

    CircularBuffer<int> buffer2(3);

    buffer2.load("buffer.bin");

    std::cout << "Elements from file: ";
    while (!buffer2.empty()) {
        std::cout << buffer2.pop() << " ";
    }
    std::cout << "\n";

    std::remove("buffer.bin");

    return 0;
}