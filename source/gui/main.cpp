#include "coral.hpp"

int main(int argc, char *argv[])
{
    Coral *app;
    int ret;

    app = Coral::instance(argc, argv);
    ret = app->run();
    Coral::drop();

    return ret;
}
