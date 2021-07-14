#ifndef MOUSE
#define MOUSE

namespace mouse
{
    int init(void);

    bool initStatus(void);

    void position(int *x, int *y);

    bool leftClick(void);

    void quit(void);
}

#endif // MOUSE