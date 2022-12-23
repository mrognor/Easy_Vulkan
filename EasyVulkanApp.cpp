#include <iostream>

#include "EV_App.h"

// Make macro or function with switch to get object
#define GET_DATA(container) \
\


class ContA : public EV::EV_VkClassContainer
{
private:
    int Chisl = 89;
public:
    ContA(EV::EV_App* app) : EV::EV_VkClassContainer(app, "int") {}

    void* GetData() override 
    {
        return ((void*)&Chisl); 
    }

    void Setup() {};
    void Create() {};
    void CleanUp() {};
};

class ContB : public EV::EV_VkClassContainer
{
private:
    std::string Msg = "dadsa";
public:
    ContB(EV::EV_App* app) : EV::EV_VkClassContainer(app, "string") {}

    void* GetData() override 
    {
        return ((void*)&Msg); 
    }

    void Setup() {};
    void Create() {};
    void CleanUp() {};
};


class MyApp : public EV::EV_App
{
private:
    ContA ACont{this};
    ContB BCont{this};
public:
    void Setup() override 
    {
        int* a = (int*)VkClasses.find("int")->second->GetData();
        std::cout << *a << std::endl;

        std::string* b = (std::string*)(VkClasses.find("string")->second->GetData());
        std::cout << *b << std::endl;

        int aa = *(int*)VkClasses.find("int")->second->GetData();
        std::cout << aa << std::endl;

        std::string bb = *(std::string*)(VkClasses.find("string")->second->GetData());
        std::cout << bb << std::endl;
    }

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