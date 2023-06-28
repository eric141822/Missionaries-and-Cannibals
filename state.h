#include <memory>
class State
{
public:
    int mRight;
    int cRight;
    int mLeft;
    int cLeft;
    int boatPos;
    std::shared_ptr<State> parent;

    State(int mRight, int cRight, int mLeft, int cLeft, int boatPos, std::shared_ptr<State> parent);

    bool isFinished();
    bool isValid();
    void print();
    bool equals(std::shared_ptr<State> s);
};
