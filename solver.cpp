#include "state.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <chrono>

typedef std::shared_ptr<State> StatePtr;
void adder(std::vector<StatePtr> &arr, StatePtr s)
{
    if (s->isValid())
    {
        arr.push_back(s);
    }
}

std::vector<StatePtr> generateNodeArray(StatePtr s)
{
    std::vector<StatePtr> arr;
    if (s->boatPos == 0)
    {
        adder(arr, std::make_shared<State>(s->mRight + 1, s->cRight + 1, s->mLeft - 1, s->cLeft - 1, 1, s)); //move 1m and 1c to right
        adder(arr, std::make_shared<State>(s->mRight + 2, s->cRight, s->mLeft - 2, s->cLeft, 1, s));         //move 2m to right
        adder(arr, std::make_shared<State>(s->mRight, s->cRight + 2, s->mLeft, s->cLeft - 2, 1, s));         //move 2c to right
        adder(arr, std::make_shared<State>(s->mRight + 1, s->cRight, s->mLeft - 1, s->cLeft, 1, s));         //move 1m to right
        adder(arr, std::make_shared<State>(s->mRight, s->cRight + 1, s->mLeft, s->cLeft - 1, 1, s));
    }
    else
    {
        adder(arr, std::make_shared<State>(s->mRight - 1, s->cRight - 1, s->mLeft + 1, s->cLeft + 1, 0, s));
        adder(arr, std::make_shared<State>(s->mRight - 2, s->cRight, s->mLeft + 2, s->cLeft, 0, s));
        adder(arr, std::make_shared<State>(s->mRight, s->cRight - 2, s->mLeft, s->cLeft + 2, 0, s));
        adder(arr, std::make_shared<State>(s->mRight - 1, s->cRight, s->mLeft + 1, s->cLeft, 0, s));
        adder(arr, std::make_shared<State>(s->mRight, s->cRight - 1, s->mLeft, s->cLeft + 1, 0, s));
    }
    return arr;
}

void path(StatePtr s)
{
    if (s == NULL)
    {
        std::cout << "No Solution Found.\n";
    }
    StatePtr tmp = s;
    std::vector<StatePtr> arr;
    while (tmp != NULL)
    {
        arr.insert(arr.begin(), tmp);
        tmp = tmp->parent;
    }
    for (auto f : arr)
    {
        f->print();
    }
    return;
}

bool contains(std::deque<StatePtr> fringe, StatePtr s)
{
    for (auto f : fringe)
    {
        if (s->equals(f))
        {
            return true;
        }
    }
    return false;
}

void solve(StatePtr start)
{
    int counter = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    if (start->isFinished())
    {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Solution Found\n";
        std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[μs]" << std::endl;
        path(start);
        return;
    }
    std::deque<StatePtr> fringe;
    fringe.push_back(start);
    while (true)
    {
        if (fringe.empty())
        {
            path(NULL);
            return;
        }
        StatePtr s = fringe.front();
        counter++;
        fringe.pop_front();
        std::vector<StatePtr> arr = generateNodeArray(s);
        for (int i = 0; i < arr.size(); i++)
        {
            if (!contains(fringe, arr[i]))
            {
                if (arr[i]->isFinished())
                {
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    std::cout << "Solution Found.\n";
                    std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[μs]" << std::endl;
                    std::cout << "States Explored = " << counter << std::endl;
                    path(arr[i]);
                    return;
                }

                fringe.push_back(arr[i]);
            }
        }
    }
}

int main()
{
    int ml, cl;
    std::cout << "Please enter the amount of missionaries and cannibals on the river's left.\nPlease note it's IMPOSSIBLE to solve with more than 3 Missionaries and 3 Cannibals\nMissionaries: ";

    std::cin >> ml;
    std::cout << "Cannibals: ";
    std::cin >> cl;
    while (ml < cl || cl > 3)
    {
        std::cout << "Invalid input. Try again." << std::endl;
        std::cout << "Missionaries: ";
        std::cin >> ml;
        std::cout << "Cannibals: ";
        std::cin >> cl;
    }
    StatePtr start(new State(0, 0, ml, cl, 0, nullptr));
    solve(start);
    return 0;
}
