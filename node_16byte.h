#ifndef NODE_16BYTE
#define NODE_16BYTE

#include <cstddef>
#include <utility>

#include "arithmetic_definition.h"
#include "error_handling.h"

template <typename TPayload>
class Node16Byte final
{
public:

    static constexpr std::size_t maxNumberOfNodes = 16777215;
    static constexpr std::size_t maxDimension = 255;

    Node16Byte(TPayload payload)
    {
        data[0] = 1;
        reinterpret_cast<TPayload&>(data[1]) = std::move(payload);
    }

    Node16Byte(std::size_t left,
               std::size_t right,
               std::size_t splittingDimension,
               Real splittingTreshold)
    {
        MC_ASSERT(left  <= maxNumberOfNodes);
        MC_ASSERT(right <= maxNumberOfNodes);
        MC_ASSERT(splittingDimension <= maxDimension);

                      left <<= 8;
        splittingDimension <<= 56;
                     right <<= 32;

                      left |= splittingDimension;
                      left |= right;

        reinterpret_cast<std::size_t&>(data) = left;
        reinterpret_cast<Real&>(data[8]) = splittingTreshold;
    }

    const TPayload& getPayload() const noexcept
    {
        MC_ASSERT(isLeafNode());
        return reinterpret_cast<const TPayload&>(data[1]);
    }

    TPayload& getPayload() noexcept
    {
        return const_cast<TPayload&>(const_cast<const Node16Byte&>(*this).getPayload());
    }

    bool isInternalNode() const noexcept
    {
        return data[0] == 0;
    }

    bool isLeafNode() const noexcept
    {
        return !isInternalNode();
    }

    std::size_t getLeft() const noexcept
    {
        MC_ASSERT(isInternalNode());
        std::size_t left;
        left = reinterpret_cast<const std::size_t&>(data);
        left >>= 8;
        left &= maxNumberOfNodes;
        return left;
    }

    std::size_t getRight() const noexcept
    {
        MC_ASSERT(isInternalNode());
        std::size_t right;
        right = reinterpret_cast<const std::size_t&>(data);
        right >>= 32;
        right &= maxNumberOfNodes;
        return right;
    }

    std::size_t getSplittingDimension() const noexcept
    {
        MC_ASSERT(isInternalNode());
        std::size_t splittingDimension;
        splittingDimension = reinterpret_cast<const std::size_t&>(data);
        splittingDimension >>= 56;
        return splittingDimension;
    }

    Real getSplittingTreshold() const noexcept
    {
        MC_ASSERT(isInternalNode());
        Real result = reinterpret_cast<const Real&>(data[8]);
        return result;
    }

private:

    static_assert(sizeof(TPayload) < 16, "The payload cannot be bigger than 15 bytes.");

    char data[16];
};

#endif // NODE_16BYTE
