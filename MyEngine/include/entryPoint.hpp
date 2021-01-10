#pragma once

#include <iostream>
#include <memory>

/**
 * @brief Has to be overriden in application using this library,
 * should return a shared_ptr to the class derived from Application.
 * 
 */
extern std::unique_ptr<MyEngine::Application> MyEngine::CreateApplication();

/**
 * @brief Starting point for the application.
 * 
 */
int main(int argc, char**argv)
{
    auto application = MyEngine::CreateApplication();

    if(!application -> initialize())
    {
        std::cout<<"[ERROR]"<<std::endl;
        std::cout << "- message  : " << "Couldn't initialize." << std::endl;
        return -1;
    } 

    if(!application -> onWindowCreate()) return -1;
    application -> startLoop();
    application.reset();

    return 0;
}