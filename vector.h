#pragma once

#include <utility>
#include <functional>

template <typename T>
class Vector {
public:
    Vector() = default;

    ~Vector() {
        delete[] items;
        items = nullptr;
        len = 0;
        capacity = 0;
    }

    Vector(const Vector<T> & other) {
        for (size_t i{}; i < other.len; ++i) {
            append(other.items[i]);
        }
    }

    Vector<T> & operator=(const Vector<T> & other) {
        if (this == &other) {
            return *this;
        }

        delete[] items;
        items = nullptr;
        len = 0;
        capacity = 0;

        for (size_t i{}; i < other.len; ++i) {
            append(other.items[i]);
        }

        return *this;
    }

    T & operator[](size_t index) {return items[index];}

    size_t size() const { return len; }

    template <typename U>
    T & append(U && item) {
        capacity = len + 1;
        T * newItems = new T[capacity]{};

        for (size_t i{}; i < len; ++i) {
            newItems[i] = std::move(items[i]);
        }
        newItems[len++] = std::forward<U>(item);

        delete[] items;
        items = newItems;

        return items[len-1];
    }

    void removeIf(std::function<bool(T&)> fn) {
        size_t writeIndex{};
        for (size_t readIndex{}; readIndex < len; ++readIndex) {
            // we only do something if we are *keeping* it
            // so, this feels backwards! study it...
            // we are shifting things down — no resizing going on
            if (!fn(items[readIndex])) {
                items[writeIndex++] = std::move(items[readIndex]);
            }
        }
        len = writeIndex;
    }

    void forEach(std::function<void(T&)> fn) const {
        for (size_t i{}; i < len; ++i) {
            fn(items[i]);
        }
    }

    class Iterator {
    private:
        size_t index;
        Vector<T> & vector;
    public:
        Iterator(Vector<T> & vector, size_t index) : vector{vector}, index{index} {
        }

        Iterator & operator++() {
            ++index;
            return *this;
        }

        T& operator*() {
            return vector.items[index];
        }

        bool operator!=(const Iterator& other) const {
            return index!= other.index;
        }

    };

    Iterator begin() {
        return Iterator(*this, 0);
    }

    Iterator end() {
        return Iterator(*this, len);
    }


private:
    size_t len{};
    size_t capacity{};
    T * items{};
};
