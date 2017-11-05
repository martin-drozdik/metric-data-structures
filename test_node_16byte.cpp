#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "node_16byte.h"
#include "arithmetic_utilities.h"

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <array>
#include <bitset>
#include <climits>
#include <string>
#include <numeric>

TEST_CASE( "Internal nodes keep their data intact", "[node_16byte]" )
{
    std::vector<int> lefts = {0, 1, 48, 255, 256, 65535, 65536, 12000000, 16777215};
    std::vector<int> rights = lefts;
    std::iota(rights.begin(), rights.end(), 0);

    std::vector<int> dimensions = {0, 1, 2, 4, 8, 15, 23, 145, 254, 255};
    std::vector<Real> splittingTresholds =
            {0.0, -0.0, 1.0, -1.0, 42.2143423, 73191897.74398,
             positiveInfinity(), negativeInfinity(), notAnumber()};

    for (auto &&left : lefts)
    {
        for (auto &&right : rights)
        {
            for (auto &&dimension : dimensions)
            {
                for (auto &&splittingTreshold : splittingTresholds)
                {
                    Node16Byte<double> node(left, right, dimension, splittingTreshold);

                    REQUIRE(node.isInternalNode());
                    REQUIRE(node.getLeft() == left);
                    REQUIRE(node.getRight() == right);
                    REQUIRE(node.getSplittingDimension() == dimension);

                    if (std::isnan(splittingTreshold))
                    {
                        REQUIRE(std::isnan(node.getSplittingTreshold()));
                    }
                    else
                    {
                        REQUIRE(node.getSplittingTreshold() == splittingTreshold);
                    }
                }
            }
        }
    }
}

using TArray = std::array<char, 15>;

void testConstructionAndRetreival(TArray array)
{
    Node16Byte<TArray> node(array);
    REQUIRE(node.isLeafNode());
    REQUIRE(node.getPayload() == array);
}

TEST_CASE( "Leaf nodes keep their data intact", "[node_16byte]" )
{
    TArray zeros{};

    TArray ones;
    std::fill(ones.begin(), ones.end(), 1);

    TArray binaryOnes;
    std::bitset<CHAR_BIT> bits(std::string(CHAR_BIT, '1'));
    char c = bits.to_ulong();
    std::fill(binaryOnes.begin(), binaryOnes.end(), c);

    testConstructionAndRetreival(zeros);
    testConstructionAndRetreival(ones);
    testConstructionAndRetreival(binaryOnes);
}
