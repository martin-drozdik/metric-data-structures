#ifndef CONTIGUOUS_OBJECT_POOL_H
#define CONTIGUOUS_OBJECT_POOL_H

#include <vector>
#include <stack>

// -----------------------------------
template <typename TObject, std::size_t capacity>
class ContiguousObjectPool final
{
public:

    ContiguousObjectPool(std::size_t reservedSize);

    ContiguousObjectPool(const ContiguousObjectPool& other)            = delete;
    ContiguousObjectPool& operator=(const ContiguousObjectPool& other) = delete;

    ContiguousObjectPool(ContiguousObjectPool&& other)                 = delete;
    ContiguousObjectPool& operator=(ContiguousObjectPool&& other)      = delete;

    template<typename... Args>
    std::size_t allocate(Args&&... args) noexcept;

    void deallocate(std::size_t index) noexcept;

          TObject& operator[] (std::size_t index) noexcept;
    const TObject& operator[] (std::size_t index) const noexcept;

    std::size_t size() const noexcept;

    ~ContiguousObjectPool() noexcept;

private:

    std::stack<std::size_t, std::vector<std::size_t>> freeIndices_;
    std::vector<TObject> objects_;
};
// -----------------------------------

template <typename TObject, std::size_t capacity>
ContiguousObjectPool<TObject, capacity>::ContiguousObjectPool(std::size_t reservedSize)
{

}


#endif // CONTIGUOUS_OBJECT_POOL_H
