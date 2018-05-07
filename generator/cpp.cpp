#include <iostream>
#include <experimental/ranges/iterator>

namespace ranges = std::experimental::ranges;

struct numbers
{
    numbers() = default;
    explicit numbers(int bound)
      : bound_{bound}
    {}

private:
    int bound_ = 0;

    struct iterator {
        using iterator_category = ranges::forward_iterator_tag;
        using value_type = int;
        using difference_type = int;
        using reference = int;
        using pointer = void;

        iterator() = default;
        explicit iterator(int pos)
          : pos_{pos}
        {}

        int operator*() const {
            return pos_;
        }
        friend bool operator==(iterator x, iterator y) {
            return x.pos_ == y.pos_;
        }
        friend bool operator!=(iterator x, iterator y) {
            return !(x == y);
        }
        iterator& operator++() {
            ++pos_;
            return *this;
        }
        iterator operator++(int) {
            auto tmp = *this;
            ++*this;
            return tmp;
        }
    private:
        int pos_ = 0;
    };
public:
    auto begin() const {
        return iterator{0};
    }
    auto end() const {
        return iterator{bound_};
    }
};

int main() {
    for (auto i : numbers(4)) {
        std::cout << i << '\n';
    }
}
