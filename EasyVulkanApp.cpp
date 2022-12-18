#include <iostream>

#include "EV_App.h"

class MyApp : public EV::EV_App
{
public:
    void Setup() override {}
    void MainLoop() override {}
};

int main() 
{
    MyApp app;

    try 
    {
        app.Run();
    } 
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}