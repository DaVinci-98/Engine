#pragma once

#include <iostream>
#include <memory>

extern std::unique_ptr<MyEngine::Application> MyEngine::CreateApplication();

int main(int argc, char**argv)
{
    auto application = MyEngine::CreateApplication();

    int err = application -> initialize();
    if(err < 0)
    {
        std::cout<<"[ERROR]"<<std::endl;
        std::cout << "- message  : " << "Couldn't initialize." << std::endl;
        return -1;
    } 

    if(!application -> onWindowCreate()) return -1;
    application -> startLoop();

    return 0;
}