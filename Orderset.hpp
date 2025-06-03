#pragma once
#include <initializer_list>
#include <iterator>
#include <list>
#include <unordered_map>

namespace libcppcom {
template <typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>>
class OrderedSet {
  private:
    using ListType = std::list<T>;
    ListType list_;
    using MapType = std::unordered_map<T, typename ListType::iterator, Hash, KeyEqual>;
    MapType map_;

  public:
    using iterator = typename ListType::iterator;
    using const_iterator = typename ListType::const_iterator;

    OrderedSet() = default;

    template <typename InputIt> OrderedSet(InputIt first, InputIt last) { insert(first, last); }

    OrderedSet(std::initializer_list<T> init) : OrderedSet(init.begin(), init.end()) {}

    std::pair<iterator, bool> insert(const T &value) {
        auto it = map_.find(value);
        if (it != map_.end()) {
            return {it->second, false};
        }
        list_.push_back(value);
        auto list_it = --list_.end();
        map_[value] = list_it;
        return {list_it, true};
    }

    template <typename InputIt> void insert(InputIt first, InputIt last) {
        for (; first != last; ++first) {
            insert(*first);
        }
    }

    size_t erase(const T &value) {
        auto it = map_.find(value);
        if (it == map_.end()) {
            return 0;
        }
        list_.erase(it->second);
        map_.erase(it);
        return 1;
    }

    iterator erase(iterator pos) {
        auto value = *pos;
        auto map_it = map_.find(value);
        if (map_it != map_.end()) {
            list_.erase(map_it->second);
            map_.erase(map_it);
        }
        return list_.begin();
    }

    bool contains(const T &value) const { return map_.find(value) != map_.end(); }

    size_t size() const { return list_.size(); }

    bool empty() const { return list_.empty(); }

    void clear() {
        list_.clear();
        map_.clear();
    }

    iterator begin() { return list_.begin(); }
    iterator end() { return list_.end(); }
    const_iterator begin() const { return list_.begin(); }
    const_iterator end() const { return list_.end(); }
    const_iterator cbegin() const { return list_.cbegin(); }
    const_iterator cend() const { return list_.cend(); }
};
}