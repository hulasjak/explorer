// A C++ Program to implement A* Search Algorithm
// source: https://www.geeksforgeeks.org/a-search-algorithm/
#include "math.h"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <SFML/Graphics.hpp>

using namespace std;

// Creating a shortcut for tuple<int, int, int> type
typedef tuple<double, int, int> Tuple;

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    sf::Vector2i parent;
    // f = g + h
    double f, g, h;
    cell()
        : parent(-1, -1)
        , f(-1)
        , g(-1)
        , h(-1)
    {
    }
};

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
template <size_t ROW, size_t COL>
class AStar
{
public:
    // A Function to find the shortest path between a given
    // source cell to a destination cell according to A* Search
    // Algorithm
    AStar(const array<array<unsigned int, COL>, ROW>& grid)
    {
        for (unsigned int i = 0; i < COL; ++i)
            for (unsigned int j = 0; j < ROW; ++j)
                _grid[i][j] = grid[j][i];
    }

    sf::Vector2i aStarSearch(sf::Vector2i const& src_v, sf::Vector2i const& dest_v)
    {
        sf::Vector2i src{src_v.x, src_v.y};
        sf::Vector2i dest{dest_v.x, dest_v.y};

        // If the source is out of range
        if (!isValid(src)) {
            throw std::runtime_error("Source is invalid");
        }

        // If the destination is out of range
        if (!isValid(dest)) {
            throw std::runtime_error("Destination is invalid");
        }

        // Either the source or the destination is blocked
        if (!isUnBlocked(src) || !isUnBlocked(dest)) {
            throw std::runtime_error("Source or the destination is blocked");
        }

        // If the destination cell is the same as source cell
        if (isDestination(src, dest)) {
            return {0, 0};
        }

        // Create a closed list and initialise it to false which
        // means that no cell has been included yet This closed
        // list is implemented as a boolean 2D array
        bool closedList[COL][ROW];
        memset(closedList, false, sizeof(closedList));

        // Declare a 2D array of structure to hold the details
        // of that cell
        array<array<cell, ROW>, COL> cellDetails;

        unsigned int i, j;
        // Initialising the parameters of the starting node
        i = src.x, j = src.y;
        cellDetails[i][j].f      = 0.0;
        cellDetails[i][j].g      = 0.0;
        cellDetails[i][j].h      = 0.0;
        cellDetails[i][j].parent = {i, j};

        /*
        Create an open list having information as-
        <f, <i, j>>
        where f = g + h,
        and i, j are the row and column index of that cell
        Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
        This open list is implemented as a set of tuple.*/
        std::priority_queue<Tuple, std::vector<Tuple>, std::greater<Tuple> > openList;

        // Put the starting cell on the open list and set its
        // 'f' as 0
        openList.emplace(0.0, i, j);

        // We set this boolean value as false as initially
        // the destination is not reached.
        while (!openList.empty()) {
            const Tuple& p = openList.top();
            // Add this vertex to the closed list
            i = get<1>(p);  // second element of tuple
            j = get<2>(p);  // third element of tuple

            // Remove this vertex from the open list
            openList.pop();
            closedList[i][j] = true;
            /*
                    Generating all the 8 successor of this cell
                            N.W N N.E
                            \ | /
                            \ | /
                            W----Cell----E
                                    / | \
                            / | \
                            S.W S S.E

                    Cell-->Popped Cell (i, j)
                    N --> North     (i-1, j)
                    S --> South     (i+1, j)
                    E --> East     (i, j+1)
                    W --> West         (i, j-1)
                    N.E--> North-East (i-1, j+1)
                    N.W--> North-West (i-1, j-1)
                    S.E--> South-East (i+1, j+1)
                    S.W--> South-West (i+1, j-1)
            */
            for (int add_x = -1; add_x <= 1; add_x++) {
                for (int add_y = -1; add_y <= 1; add_y++) {
                    sf::Vector2i neighbour{i + add_x, j + add_y};
                    // Only process this cell if this is a valid
                    // one
                    if (isValid(neighbour)) {
                        // If the destination cell is the same
                        // as the current successor
                        if (isDestination(neighbour,
                                          dest)) {  // Set the Parent of
                                                    // the destination cell
                            cellDetails[neighbour.x][neighbour.y].parent = {i, j};

                            auto path = tracePath(cellDetails, dest);
                            if (path.x == 0 && path.y == 0)
                                return sf::Vector2i{dest - src};

                            return path;
                        }
                        // If the successor is already on the
                        // closed list or if it is blocked, then
                        // ignore it.  Else do the following
                        else if (!closedList[neighbour.x][neighbour.y] && isUnBlocked(neighbour)) {
                            double gNew, hNew, fNew;
                            gNew = cellDetails[i][j].g + 1.0;
                            hNew = calculateHValue(neighbour, static_cast<sf::Vector2i>(dest));
                            fNew = gNew + hNew;

                            // If it isn’t on the open list, add
                            // it to the open list. Make the
                            // current square the parent of this
                            // square. Record the f, g, and h
                            // costs of the square cell
                            //             OR
                            // If it is on the open list
                            // already, check to see if this
                            // path to that square is better,
                            // using 'f' cost as the measure.
                            if (cellDetails[neighbour.x][neighbour.y].f == -1 ||
                                cellDetails[neighbour.x][neighbour.y].f > fNew) {
                                openList.emplace(fNew, neighbour.x, neighbour.y);

                                // Update the details of this
                                // cell
                                cellDetails[neighbour.x][neighbour.y].g      = gNew;
                                cellDetails[neighbour.x][neighbour.y].h      = hNew;
                                cellDetails[neighbour.x][neighbour.y].f      = fNew;
                                cellDetails[neighbour.x][neighbour.y].parent = {i, j};
                            }
                        }
                    }
                }
            }
        }

        // When the destination cell is not found and the open
        // list is empty, then we conclude that we failed to
        // reach the destination cell. This may happen when the
        // there is no way to destination cell (due to
        // blockages)
        throw std::runtime_error("Failed to find the Destination Cell\n");
    }

private:
    array<array<int, ROW>, COL> _grid;
    bool isValid(const sf::Vector2i& point)
    {  // Returns true if row number and column number is in
       // range
        if (ROW > 0 && COL > 0)
            return (point.x >= 0) && (point.x < COL) && (point.y >= 0) && (point.y < ROW);

        return false;
    }

    // A Utility Function to check whether the given cell is
    // blocked or not
    bool isUnBlocked(const sf::Vector2i& point)
    {
        // Returns true if the cell is not blocked else false
        return isValid(point) && _grid[point.x][point.y] == 1;
    }

    // A Utility Function to check whether destination cell has
    // been reached or not
    bool isDestination(const sf::Vector2i& position, const sf::Vector2i& dest) { return position == dest; }
    // bool isDestination(const sf::Vector2i& position, const sf::Vector2i& dest) { return position == dest; }

    // A Utility Function to calculate the 'h' heuristics.
    double calculateHValue(const sf::Vector2i& src, const sf::Vector2i& dest)
    {
        // h is estimated with the two points distance formula
        return sqrt(pow((src.x - dest.x), 2.0) + pow((src.y - dest.y), 2.0));
    }

    // A Utility Function to trace the path from the source to
    // destination
    sf::Vector2i tracePath(const array<array<cell, ROW>, COL>& cellDetails, const sf::Vector2i& dest)
    {
        // printf("\nThe Path is ");

        stack<sf::Vector2i> Path;

        int row                = dest.x;
        int col                = dest.y;
        sf::Vector2i next_node = cellDetails[row][col].parent;
        do {
            Path.push(next_node);
            next_node = cellDetails[row][col].parent;
            row       = next_node.x;
            col       = next_node.y;
        } while (cellDetails[row][col].parent != next_node);

        Path.emplace(row, col);
        while (!Path.empty()) {
            auto p1 = static_cast<sf::Vector2i>(Path.top());
            Path.pop();
            auto p2 = static_cast<sf::Vector2i>(Path.top());

            // printf("-> (%d,%d) ", p2.x - p1.x, p2.y - p1.y);
            return p2 - p1;
        }
        throw std::runtime_error("Failed to find the Destination Cell\n");
    }
};
