#include <vector>

namespace ds
{
    template <typename ValueType>
    class Queue {
    private:
    
    public:
        Queue() = default;
        ~Queue() = default;
        

        std::vector<ValueType> data;
        Queue<ValueType> operator=(const std::vector<ValueType> &source) {
            data = source;
            return *this;
        }
        /// Places an element at queue's rear end 
        void enqueue(const ValueType &a) {
            data.push_back(a);
        }
        /// Pops the next element in the queue 
        ValueType dequeue() {
            if (empty()) {
                // Nothing
            }
            else {
                auto first{data[0]};
                data.erase(data.begin());
                return first;
            }
        }

        /// 
    
        /// Returns the number of elements in the queue
        int size() {
            return data.size();
        }
        /// Returns 'true' if the queue is empty 
        bool empty() {
            return data.empty();
        }

        ValueType * begin() {
            return &data[0];
        }
        ValueType *end() {
            return &data[data.size() - 1];
        }
        ValueType back () {
            return data.back();
        }
    };

    template <typename ValueType>
    class Stack {
    private:
        

    public:
        Stack() = default;
        ~Stack() = default;


        std::vector<ValueType> data;
        
        ValueType get_upper() {
            return data.back();
        }
        void push(const ValueType &a) {
            data.push_back(a);
        }
        /// Removes the upper element of the stack
        ValueType pop() {
            auto last{data.back()};
            data.pop_back();
            return last;
        }
        /// A 'pop' method intended specifically for this BARES implementation.
        /// It returns a pair of the two upper elements of the stack
        std::pair<ValueType, ValueType> pop_operands() {
            ValueType value1{pop()};
            ValueType value2{pop()};
            return std::make_pair(value1, value2);
        }

        /// A functionally made especifically for this BARES implementation. It releases all of the elements in a stack into a vector
        /// @return A vector containing the contents in the stack, preserving the original order
        std::vector<ValueType> free_all() {
            std::vector<ValueType> vec;
            for (ValueType e : data) {
                vec.push_back(e);
            }
            return vec;
        }
        /// Returns the size of the data vector 
        int size() {
            return data.size();
        }
        /// Returns true if the data vector is empty 
        bool empty() {
            return data.empty();
        }
        /// Returns the last element of the data block 
        ValueType back() {
            return data.back();
        }
    };
}