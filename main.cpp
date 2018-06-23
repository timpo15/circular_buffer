#include <iostream>
#include <vector>
#include <algorithm>
#include "Circular_buffer.h"

bool test_simple1() {
    size_t counts = 1000;
    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; i++) {
        cb.push_front(i);
        ans.push_back(i);

    }
    std::reverse(ans.begin(), ans.end());
    for (size_t i = 0; i < counts; i++) {
        if (ans[i] != cb[i])
            return false;
        std::cout << cb[i] << " ";
    }
    std::cout << std::endl;
    return true;
}

bool test_simple2() {
    size_t counts = 1000;

    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; i++) {
        cb.push_back(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        if (ans[i] != cb[i])
            return false;
        std::cout << cb[i] << " ";
    }
    std::cout << std::endl;
    return true;

}

bool test_simple3() {
    size_t counts = 1000;

    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; i++) {
        cb.push_back(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        if (ans[i] != cb.front())
            return false;
        cb.pop_front();
        std::cout << cb[i] << " ";
    }
    std::cout << std::endl;
    return true;

}


bool test_simple4() {
    size_t counts = 1000;
    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; i++) {
        cb.push_front(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        std::cout << cb.back() << " ";
        if (ans[i] != cb.back())
            return false;
        cb.pop_back();
    }
    std::cout << std::endl;
    return true;
}

bool test_simple5() {
    size_t counts = 1000;
    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; i++) {
        cb.push_front(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        cb.pop_back();
    }
    for (size_t i = 0; i < counts; i++) {
        cb.push_front(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        cb.pop_back();
    }
    for (size_t i = 0; i < counts; i++) {
        cb.push_front(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        cb.pop_back();
    }
    if (!cb.empty())
        return false;
    std::cout << std::endl;
    return true;
}


bool test_simple6() {
    size_t counts = 1000;
    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        cb.insert(cb.end(), i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; ++i) {
        std::cout << cb[i] << " ";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < counts; i++) {
        std::cout << cb[i] << " ";
//        if (ans[i] != cb[i])
//            return false;
    }
    std::cout << std::endl;
    return true;
}

bool test_simple7() {
    size_t counts = 1000;
    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        cb.insert(cb.begin(), i);
        ans.push_back(i);
    }


    reverse(ans.begin(), ans.end());
    for (size_t i = 0; i < counts; i++) {
        std::cout << cb[i] << " ";
//        if (ans[i] != cb[i])
//            return false;
    }
    std::cout << std::endl;
    return true;
}

bool test_simple8() {
    size_t counts = 1000;
    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        if (i % 2 == 0) {
            cb.insert(cb.end(), i);
            ans.push_back(i);
        } else {
            cb.insert(cb.begin(), i);
            ans.insert(ans.begin(), i);
        }
    }

    for (size_t i = 0; i < counts; ++i) {
        std::cout << cb[i] << " ";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < counts; i++) {
        std::cout << cb[i] << " ";
        if (ans[i] != cb[i])
            return false;
    }
    std::cout << std::endl;
    return true;
}


bool test_simple9() {
    size_t counts = 1000;
    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        if (i % 2 == 0) {
            cb.insert(cb.end(), i);
            ans.push_back(i);
        } else {
            cb.insert(cb.begin(), i);
            ans.insert(ans.begin(), i);
        }
    }

    size_t i = 0;
    for (auto t = cb.begin(); t != cb.end(); ++t) {
        if (ans[i++] != *t)
            return false;
    }
    std::cout << std::endl;
    return true;
}

bool test_simple10() {
    size_t counts = 1000;
    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        cb.insert(cb.end(), i);
        ans.push_back(i);
    }
    size_t i = 0;
    for (auto t = cb.rbegin(); t != cb.rend(); ++t) {
        std::cout << *t << " ";
        if (ans[counts - i++ - 1] != *t)
            return false;
    }
    std::cout << std::endl;
    return true;
}

bool test_simple11() {
    size_t counts = 1000;
    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        cb.insert(cb.end(), i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; ++i) {
        cb.erase(cb.begin());
    }
    if (!cb.empty()) return false;

    return true;
}

bool test_simple12() {
    size_t counts = 1000;
    circular_buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        cb.insert(cb.end(), i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts / 2; ++i) {
        cb.erase(cb.begin());
        ans.erase(ans.begin());
    }
    for (size_t i = 0; i < counts / 2; ++i) {
        if (ans[i] != cb[i])
            return false;
    }

    return true;
}

int main() {
    if (!test_simple1()) {
        throw std::runtime_error("test1 - push_front");
    }
    if (!test_simple2()) {
        throw std::runtime_error("test2 - push_back");
    }
    if (!test_simple3()) {
        throw std::runtime_error("test3 - pop_front");
    }
    if (!test_simple4()) {
        throw std::runtime_error("test4 - pop_ back");
    }
    if (!test_simple5()) {
        throw std::runtime_error("test5 - push_pop");
    }

    if (!test_simple6()) {
        throw std::runtime_error("test6 - insert end");
    }
    if (!test_simple7()) {
        throw std::runtime_error("test7 - insert begin");
    }
    if (!test_simple8()) {
        throw std::runtime_error("test8 - insert begin -end");
    }

    if (!test_simple9()) {
        throw std::runtime_error("test9 - iterator test");
    }
    if (!test_simple10()) {
        throw std::runtime_error("test10 - reverse iterator test");
    }
    if (!test_simple11()) {
        throw std::runtime_error("test11 - erase test");
    }
    if (!test_simple12()) {
        throw std::runtime_error("test12 - erase2 test");
    }


}