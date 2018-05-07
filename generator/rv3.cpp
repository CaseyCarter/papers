#include <iostream>
#include <range/v3/view_facade.hpp>

struct numbers
  : ranges::view_facade<numbers>
{
    friend ranges::range_access;

    numbers() = default;
    explicit numbers(int bound)
      : bound_{bound}
    {}

private:
    int bound_ = 0;

    struct cursor {
        cursor() = default;
        explicit cursor(int pos)
          : pos_{pos}
        {}

        int read() const {
            return pos_;
        }
        bool equal(cursor x) const {
            return pos_ == x.pos_;
        }
        void next() { ++pos_; }
#if FOO
        void prev() { --pos_; }
        void advance(int n) { pos_ += n; }
        int distance_to(cursor x) const { return x.pos_ - pos_; }
#endif
    private:
        int pos_ = 0;
    };

    auto begin_cursor() const {
        return cursor{0};
    }
    auto end_cursor() const {
        return cursor{bound_};
    }
};

int main() {
#if FOO
    static_assert(ranges::RandomAccessView<numbers>());
#else
    static_assert(ranges::ForwardView<numbers>());
#endif
    for (auto i : numbers(4)) {
        std::cout << i << '\n';
    }
}
