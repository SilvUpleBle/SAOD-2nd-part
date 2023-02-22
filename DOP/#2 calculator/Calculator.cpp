#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[])
{
    std::vector<std::string> arguments(argv + 1, argv + argc);
    if (arguments.size() > 3)
    {
        std::cout << "Too many arguments!" << std::endl;
    }
    else
    {
        try
        {
            if (arguments[0] == "sub" || arguments[0] == "add" || arguments[0] == "mul" || arguments[0] == "div")
            {
                if (arguments[0] == "sub")
                {
                    std::cout << std::stoi(arguments[1]) - std::stoi(arguments[2]);
                    return 0;
                }
                if (arguments[0] == "add")
                {
                    std::cout << std::stoi(arguments[1]) + std::stoi(arguments[2]);
                    return 0;
                }
                if (arguments[0] == "mul")
                {
                    std::cout << std::stoi(arguments[1]) * std::stoi(arguments[2]);
                    return 0;
                }
                if (arguments[0] == "div")
                {
                    if (arguments[2] != "0")
                    {
                        std::cout << std::stoi(arguments[1]) / double(std::stoi(arguments[2]));
                    }
                    else
                        std::cout << "Division by zero" << std::endl;
                    return 0;
                }
            }
            else
                std::cout << "Unknown command!";
        }
        catch (const std::exception&)
        {
            std::cout << "Error with numbers. Check and try againg!";
        }
    }
}