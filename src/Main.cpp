#include "Application.h"

int main(int _argc, char** _argv)
{
    Application app("Minecraft");
    app.runLoop(_argc, _argv);
    return 0;
}