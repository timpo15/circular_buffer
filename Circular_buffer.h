//
// Created by timpo on 23.06.18.
//

#ifndef CIRCULAR_BUFFER_CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_CIRCULAR_BUFFER_H

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
struct circular_buffer {
private:
    size_t size_;
    size_t begin_;
    size_t capacity_;
    T *data_ = nullptr;

    template<typename V>
    struct basic_iterator;

    void ensure_capacity(size_t new_size);

    void destroy_objects();

public:

    using iterator = basic_iterator<T>;
    using const_iterator = basic_iterator<const T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    circular_buffer();

    explicit circular_buffer(size_t const &size);

    circular_buffer(circular_buffer<T> const &other);

    circular_buffer &operator=(circular_buffer const &other);

    ~circular_buffer();


    void push_back(T const &a);

    void push_front(T const &a);

    void pop_back();

    void pop_front();

    T const &back() const;

    T &back();

    T const &front() const;

    T &front();

    T &operator[](size_t index);

    T const &operator[](size_t index) const;

    size_t size();

    bool empty();

    void clear();

    iterator insert(const_iterator pos, T const &value);

    iterator erase(const_iterator pos);

    iterator begin();

    const_iterator begin() const;

    iterator end();

    const_iterator end() const;

    reverse_iterator rbegin();

    const_reverse_iterator rbegin() const;

    reverse_iterator rend();

    const_reverse_iterator rend() const;

    void swap(circular_buffer<T> &other);
};


template<typename T>
template<typename V>
struct circular_buffer<T>::basic_iterator {
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = V;
    using pointer = V *;
    using reference = V &;

    basic_iterator() = default;

    basic_iterator(T *data, size_t ind, size_t capacity) : ind_(ind), capacity_(capacity), data_(data) {}

    template<typename U>
    basic_iterator(basic_iterator<U> const &other,
                   typename std::enable_if<std::is_same<U const, V>::value &&
                                           std::is_const<V>::value>::type * = nullptr) {
        this->data_ = other.data_;
        this->capacity_ = other.capacity_;
        this->ind_ = other.ind_;
    }

    uint64_t get_ind() {
        return ind_;
    }

    basic_iterator &operator=(basic_iterator const &) = default;

    reference operator*() const {
        return data_[ind_];
    };

    pointer operator->() const;

    basic_iterator &operator++() {
        ind_ = (ind_ + 1) % capacity_;
        return *this;
    };

    basic_iterator operator++(int) {
        basic_iterator tmp(*this);
        ++*this;
        return tmp;
    }

    basic_iterator &operator--() {
        ind_ = (capacity_ + ind_ - 1) % capacity_;
        return *this;
    }

    basic_iterator operator--(int) {
        basic_iterator tmp(*this);
        --*this;
        return tmp;
    }

    basic_iterator operator-(size_t lhs) {
        return basic_iterator<V>(data_, (capacity_ + ind_ - lhs) % capacity_, capacity_);
    }

    basic_iterator &operator-=(size_t lhs) {
        *this = *this - lhs;
        return *this;
    }

    basic_iterator &operator+=(size_t lhs) {
        *this = *this + lhs;
        return *this;
    }

    basic_iterator operator+(int64_t shift) {
        return basic_iterator<V>(data_, (ind_ + shift) % capacity_, capacity_);
    }

    bool operator<(basic_iterator<const V> const &lhs) {
        return ind_ < lhs.ind_;
    }

    bool operator>(basic_iterator<const V> const &lhs) {
        return ind_ < lhs.ind_;
    }

    bool operator>=(basic_iterator<const V> const &lhs) {
        return ind_ < lhs.ind_;
    }

    bool operator<=(basic_iterator<const V> const &lhs) {
        return ind_ < lhs.ind_;
    }


    friend bool operator==(basic_iterator const &a, basic_iterator const &b) {
        return a.ind_ == b.ind_;
    }

    friend bool operator!=(basic_iterator const &a, basic_iterator const &b) {
        return a.ind_ != b.ind_;
    }

private:
    size_t ind_ = 0;
    size_t capacity_{};
    T *data_;
    friend struct circular_buffer;
};


template<typename T>
void circular_buffer<T>::ensure_capacity(size_t new_size) {
    if (capacity_ <= new_size) {
        circular_buffer<T> temp((capacity_ + 1) * 2);
        for (size_t i = 0; i < size_; ++i) {
            temp.push_back(T((*this)[i]));
        }
        temp.swap(*this);
    }
}

template<typename T>
void circular_buffer<T>::destroy_objects() {
    for (size_t i = 0; i < size_; ++i) {
        (*this)[i].~T();
    }
}

template<typename T>
circular_buffer<T>::circular_buffer() :size_(0), begin_(0), capacity_(0) {}

template<typename T>
circular_buffer<T>::circular_buffer(size_t const &size) :size_(0), begin_(0), capacity_(size + 4) {
    data_ = static_cast<T *>(operator new(sizeof(T) * capacity_));
}

template<typename T>
circular_buffer<T>::~circular_buffer() {
    destroy_objects();
    operator delete(data_);
}

template<typename T>
circular_buffer<T>::circular_buffer(const circular_buffer<T> &other):  size_(0), begin_(other.begin_),
                                                                       capacity_(other.capacity_), data_(nullptr) {
    if (capacity_ == 0)
        return;
//    std::uninitialized_fill(other.begin(), other.end(), data_);
    data_ = static_cast<T *>(operator new(sizeof(T) * capacity_ + 4));
    try {
        for (size_t i = 0; i < other.size_; ++i) {
            push_back(other[i]);
        }
    } catch (...) {
        destroy_objects();
        delete data_;
        throw;
    }
}

template<typename T>
circular_buffer<T> &circular_buffer<T>::operator=(circular_buffer<T> const &other) {
    circular_buffer<T> tmp(other);
    this->swap(tmp);
    return *this;
}

template<typename T>
void circular_buffer<T>::push_back(const T &a) {
    ensure_capacity(size_ + 1);
    new(&data_[(begin_ + size_) % capacity_]) T(a);
    ++size_;
}

template<typename T>
void circular_buffer<T>::push_front(const T &a) {
    ensure_capacity(size_ + 1);
    new(&data_[((capacity_ + begin_) - 1) % capacity_]) T(a);
    begin_ = ((capacity_ + begin_) - 1) % capacity_;
    ++size_;
}

template<typename T>
void circular_buffer<T>::pop_back() {
    data_[((capacity_ + begin_ + size_) - 1) % capacity_].~T();
    --size_;
}

template<typename T>
void circular_buffer<T>::pop_front() {
    data_[begin_].~T();
    --size_;
    begin_ = (begin_ + 1) % capacity_;
}

template<typename T>
T const &circular_buffer<T>::back() const {
    return data_[((capacity_ + begin_ + size_) - 1) % capacity_];
}

template<typename T>
T &circular_buffer<T>::back() {
    return data_[((capacity_ + begin_ + size_) - 1) % capacity_];
}

template<typename T>
T const &circular_buffer<T>::front() const {
    return data_[begin_];
}

template<typename T>
T &circular_buffer<T>::front() {
    return data_[begin_];
}

template<typename T>
T &circular_buffer<T>::operator[](size_t index) {
    return data_[(index + begin_ + capacity_) % capacity_];
}

template<typename T>
T const &circular_buffer<T>::operator[](size_t index) const {
    return data_[(index + begin_ + capacity_) % capacity_];

}

template<typename T>
bool circular_buffer<T>::empty() {
    return size_ == 0;
}

template<typename T>
void circular_buffer<T>::clear() {
    destroy_objects();
    begin_ = 0;
    size_ = 0;
}

template<typename T>
typename circular_buffer<T>::iterator circular_buffer<T>::insert(const_iterator pos, T const &value) {
    size_t length_begin = pos.get_ind() >= begin_ ? pos.get_ind() - begin_ : pos.get_ind() + (capacity_ - begin_);
//    size_t length_begin = 0;
    if (length_begin <= size_ / 2) {
        size_t pos_ind = pos.get_ind() >= begin_ ? pos.get_ind() - begin_ : pos.get_ind() + (capacity_ - begin_);
        push_front(value);
        iterator it = begin();
        using std::swap;
        for (size_t i = 0; i < pos_ind; ++i) {
            swap(*it, *(it + 1));
            ++it;
        }
        return it;

    } else {
        size_t temp = (begin_ + size_) % capacity_;
        size_t pos_ind = pos.get_ind() <= temp ? temp - pos.get_ind() :
                          capacity_ - pos.get_ind() + temp;
        push_back(value);
        iterator it = end() - 1;
        using std::swap;
        for (size_t i = 0; i < pos_ind; ++i) {
            swap(*it, *(it - 1));
            --it;
        }
        return it;
    }

}

template<typename T>
typename circular_buffer<T>::iterator circular_buffer<T>::erase(const_iterator pos) {
    size_t ind = pos.get_ind();
    size_t length_begin = ind >= begin_ ? ind - begin_ : ind + (capacity_ - begin_);
    iterator cur = iterator(data_, ind, capacity_);
    if (length_begin <= size_ / 2) {
        while (cur != begin()) {
            *cur = *(cur - 1);
            cur--;
        }
        pop_front();
    } else {
        while (cur != end() - 1) {
            *cur = *(cur + 1);
            cur++;
        }
        pop_back();
    }
    return iterator(data_, (ind + 1) % capacity_, capacity_);

}

template<typename T>
typename circular_buffer<T>::iterator circular_buffer<T>::begin() {
    return basic_iterator<T>(data_, begin_, capacity_);
}

template<typename T>
typename circular_buffer<T>::const_iterator circular_buffer<T>::begin() const {
    return basic_iterator<T>(data_, begin_, capacity_);

}

template<typename T>
typename circular_buffer<T>::iterator circular_buffer<T>::end() {
    if (capacity_ == 0) {
        return basic_iterator<T>(data_, (static_cast<uint64_t >(begin_ + size_)), capacity_);
    } else return basic_iterator<T>(data_, (static_cast<uint64_t >(begin_ + size_)) % capacity_, capacity_);
}

template<typename T>
typename circular_buffer<T>::const_iterator circular_buffer<T>::end() const {
    if (capacity_ == 0) {
        return basic_iterator<T>(data_, (static_cast<uint64_t >(begin_ + size_)), capacity_);
    } else return basic_iterator<T>(data_, (static_cast<uint64_t >(begin_ + size_)) % capacity_, capacity_);
}

template<typename T>
typename circular_buffer<T>::reverse_iterator circular_buffer<T>::rbegin() {
    return std::reverse_iterator<iterator>(end());
}

template<typename T>
typename circular_buffer<T>::const_reverse_iterator circular_buffer<T>::rbegin() const {
    return std::reverse_iterator<const_iterator>(end());
}

template<typename T>
typename circular_buffer<T>::reverse_iterator circular_buffer<T>::rend() {
    return std::reverse_iterator<iterator>(begin());
}

template<typename T>
typename circular_buffer<T>::const_reverse_iterator circular_buffer<T>::rend() const {
    return std::reverse_iterator<const_iterator>(begin());
}


template<typename T>
void circular_buffer<T>::swap(circular_buffer<T> &other) {
    std::swap(data_, other.data_);
    std::swap(begin_, other.begin_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template<typename T>
size_t circular_buffer<T>::size() {
    return size_;
}

template<typename T>
void swap(circular_buffer<T> &lhs, circular_buffer<T> &rhs) {
    lhs.swap(rhs);
};

#endif //CIRCULAR_BUFFER_CIRCULAR_BUFFER_H
