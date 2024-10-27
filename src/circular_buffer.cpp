#include <vector>
#include<string>
#include<optional>

template<typename T>

class CircularBuffer {
    private:
        std::vector<T> buffer;
        size_t head = 0;
        size_t tail = 0;
        bool is_full = false;

    public:
        explicit CircularBuffer(size_t size): buffer(size) {}

        void enqueue(T item) {
            if (is_full) {
            std::cout << "Buffer is full. Overwriting the oldest item.\n";
            tail = (tail + 1) % buffer.size(); 
            }
            buffer[head] = item;
            head = (head + 1) % buffer.size();
            is_full = (head == tail);
        }

        std::optional dequeue() {
            if (is_empty()) {
                std::cout << "Buffer is empty \n";
                return std::nullopt;
            }
            T item = buffer[tail];
            tail = (tail + 1) % buffer.size();
            is_full = false
            return item;
        }

        bool is_empty() const {
            return !is_full() && head == tail;
        }

        bool is_full() const {return is_full}

        size_t size() const {
            if (is_full) {
                return buffer.size();
            }
            if (head >= tail) {
                return head - tail;
            }
            return buffer.size() - (tail - head);
        }
};