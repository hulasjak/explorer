#include "gtest/gtest.h"
#include "explorer/a_star_impl.hpp"

#define ROWS 3
#define COLS 6

std::array<std::array<unsigned int, COLS>, ROWS> arr;

TEST(AstarTests, AtDestination)
{
    for (auto& row : arr) {
        row.fill(1);
    }

    AStar<ROWS, COLS> a(arr);
    auto move = a.aStarSearch(sf::Vector2i{0, 0}, sf::Vector2i{0, 0});

    EXPECT_EQ(move.x, 0);
    EXPECT_EQ(move.y, 0);
}

TEST(AstarTests, MoveToNext)
{
    for (auto& row : arr) {
        row.fill(1);
    }

    AStar<ROWS, COLS> a(arr);
    auto move = a.aStarSearch(sf::Vector2i{0, 0}, sf::Vector2i{0, 1});

    EXPECT_EQ(move.x, 0);
    EXPECT_EQ(move.y, 1);
}

TEST(AstarTests, MoveY)
{
    for (auto& row : arr) {
        row.fill(1);
    }

    AStar<ROWS, COLS> a(arr);
    auto move = a.aStarSearch(sf::Vector2i{0, 0}, sf::Vector2i{0, 2});
    EXPECT_EQ(move.x, 0);
    EXPECT_EQ(move.y, 1);
}

TEST(AstarTests, MoveX)
{
    for (auto& row : arr) {
        row.fill(1);
    }

    AStar<ROWS, COLS> a(arr);
    auto move = a.aStarSearch(sf::Vector2i{0, 0}, sf::Vector2i{2, 0});

    EXPECT_EQ(move.x, 1);
    EXPECT_EQ(move.y, 0);
}

TEST(AstarTests, MoveAvoid)
{
    for (auto& row : arr) {
        row.fill(1);
    }

    arr[0][1] = 0;
    arr[1][1] = 0;

    AStar<ROWS, COLS> a(arr);
    auto move = a.aStarSearch(sf::Vector2i{0, 0}, sf::Vector2i{2, 0});

    EXPECT_EQ(move.x, 0);
    EXPECT_EQ(move.y, 1);
}

TEST(AstarTests, MoveNearEnd)
{
    for (auto& row : arr) {
        row.fill(1);
    }

    arr[0][1] = 0;
    arr[1][1] = 0;

    AStar<ROWS, COLS> a(arr);
    auto move = a.aStarSearch(sf::Vector2i{0, 0}, sf::Vector2i{5, 0});

    EXPECT_EQ(move.x, 0);
    EXPECT_EQ(move.y, 1);
}