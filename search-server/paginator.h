#pragma once
#include <iostream>
#include "document.h"
#include <string>

template<typename It>//работает!
class IteratorRange {
public:
    IteratorRange(It begin, It end)
        : begin_(begin)
        , end_(end) {
    }
    It begin() const {
        return begin_;
    }

    It end() const {
        return end_;
    }


private:
    It begin_;
    It end_;
};



template <typename It>
class Paginator {
public:
    Paginator(It begin, It end, size_t size) {
        size_t page_num = 0;
        It page_begin = begin;
        It page_end = begin;
        for (auto i = 0; i != std::distance(begin, end); i++) {
            page_num += 1;
            std::advance(page_end, 1);
            if (page_num == size) {
                pages_.emplace_back(page_begin, page_end);
                page_begin = page_end;
                page_num = 0;
            }
        }
        if (page_begin != end) {
            pages_.emplace_back(page_begin, end);
        }
    }

    auto begin() const {
        return pages_.begin();
    }

    auto end() const {
        return pages_.end();
    }

private:
    std::vector<IteratorRange<It>> pages_;
};

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(std::begin(c), std::end(c), page_size);
}

std::string PrintDocument(const Document& doc) {
    int id = doc.id;
    double relevance = doc.relevance;
    int rating = doc.rating;
    return "{ document_id = " + std::to_string(id) +
        ", relevance = " + std::to_string(relevance) +
        ", rating = " + std::to_string(rating) + " }";
}

template<typename It>
std::ostream& operator<<(std::ostream& out, const IteratorRange<It>& range) {
    It begin = range.begin();
    It end = range.end();
    while (begin != end) {
        out << PrintDocument(*begin);
        advance(begin, 1);
    }
    return out;
}