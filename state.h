class State
{
public:
    int mRight;
    int cRight;
    int mLeft;
    int cLeft;
    int boatPos;
    State *parent;

    State(int mRight, int cRight, int mLeft, int cLeft, int boatPos, State *parent);

    bool isFinished();
    bool isValid();
    void print();
    bool equals(State *s);
};