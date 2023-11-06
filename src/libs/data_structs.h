#include <vector>

namespace ds
{
    template <typename ValueType>
    class Queue
    {
    private:
    public:
        Queue() = default;
        ~Queue() = default;
        std::vector<ValueType> data; // DEve voltar ao private!!
        Queue<ValueType> operator=(const std::vector<ValueType> &source) {
            data = source;
            return *this;
        }
        void enqueue(const ValueType &a) {
            data.push_back(a);
        }
        ValueType dequeue() {
            if (empty())
            {
                // Nothing
            }
            else
            {
                auto first{data[0]};
                data.erase(data.begin());
                return first;
            }
        }
        int size(){
            return data.size();
        }
        bool empty() {
            return data.empty();
        }
        ValueType * begin() {
            return &data[0];
        }
        ValueType *end() {
            return &data[data.size() - 1];
        }
    };

    template <typename ValueType>
    class Stack {
    private:
        std::vector<ValueType> data;

    public:
        Stack() = default;
        ~Stack() = default;
        ValueType get_upper()
        {
            return data.back();
        }
        void push(const ValueType &a) {
            data.push_back(a);
        }
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

        std::vector<ValueType> free_all() {
            std::vector<ValueType> r;
            int counter{0};
            while (counter < size())
            {
                r.push_back(pop());
            }
            return r;
        }
        int size() {
            return data.size();
        }
        bool empty() {
            return data.empty();
        }
    };
}