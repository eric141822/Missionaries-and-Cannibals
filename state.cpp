#include "state.h"
#include <iostream>
typedef std::shared_ptr<State> StatePtr;
State::State(int mRight, int cRight, int mLeft, int cLeft, int boatPos, StatePtr parent)
{
    this->mRight = mRight;
    this->cRight = cRight;
    this->mLeft = mLeft;
    this->cLeft = cLeft;
    this->boatPos = boatPos;
    this->parent = parent;
}

bool State::isFinished()
{
    return (this->mLeft == 0 && this->cLeft == 0);
}

bool State::isValid()
{
    if (this->mLeft >= 0 && this->cLeft >= 0 && this->mRight >= 0 && this->cRight >= 0 && (this->mRight == 0 || this->mRight >= this->cRight) && (this->mLeft == 0 || this->mLeft >= this->cLeft))
    {
        return true;
    }
    return false;
}

void State::print()
{
    if (boatPos == 0)
    {
        std::cout << "Cannibal_left = " << cLeft << ", Missonary_left = " << mLeft << ", Boat on Left, "
                  << "Cannibal_right = " << cRight << ", Missonary_right = " << mRight;
    }
    else
    {
        std::cout << "Cannibal_left = " << cLeft << ", Missonary_left = " << mLeft << ", Boat on Right, "
                  << "Cannibal_right = " << cRight << ", Missonary_right = " << mRight;
    }
    std::cout << std::endl;
}

bool State::equals(StatePtr s)
{
    return (s->mLeft == this->mLeft && s->cLeft == this->cLeft && s->mRight == this->mRight && s->cRight == this->cRight && s->boatPos == this->boatPos);
}