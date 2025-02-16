#pragma once
#include <deque>
#include "search_server.h"
#include "document.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);

    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        if ((SearchServer_.FindTopDocuments(raw_query, document_predicate)).empty()) {
            requests_.push_back({ 1, 0 });
        }
        else {
            requests_.push_back({ 0, 1 });
        }
        if (requests_.size() > min_in_day_) {
            requests_.pop_front();
        }
        return SearchServer_.FindTopDocuments(raw_query, document_predicate);
    }


    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);


    std::vector<Document> AddFindRequest(const std::string& raw_query);


    int GetNoResultRequests() const;
private:
    struct QueryResult {
        bool NullRes_;
        bool NotNullRes_;
    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    const SearchServer& SearchServer_;
};