#ifndef BAR_BAR_HPP_
#define BAR_BAR_HPP_

#include <memory>

namespace detail
{
    size_t * thread_id()
    {
        static thread_local size_t tss_id = -1u;
        return &tss_id;
    }
}

template <size_t STORAGE_SIZE>
struct SomeType
{
    SomeType() {}

    void set(size_t value) { *detail::thread_id() = value; }
    size_t get() { return *detail::thread_id(); }
};

std::shared_ptr<SomeType<128>> bar();

#endif // BAR_BAR_HPP_
