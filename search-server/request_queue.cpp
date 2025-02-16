#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server) 
:SearchServer_(search_server) {
}








std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    return AddFindRequest(
        raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
            return document_status == status;
        });
}



std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    return AddFindRequest(raw_query, [](int, DocumentStatus status, int) {return status == DocumentStatus::ACTUAL; });
}


int RequestQueue::GetNoResultRequests() const {
        int no_result_count = 0;
        for (const auto& result : requests_) {
            if (result.NullRes_) {
                no_result_count += 1;
            }
        }
        return no_result_count;
    }