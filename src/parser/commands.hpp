#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "callable.hpp"

#include <memory>
#include <map>
#include <string>

class CommandPool 
{
public:
    static CommandPool& getInstance();

    void registerCommand(Callable*);
    Callable* findCommand(const std::string&);

private:
    CommandPool() = default;
    CommandPool(const CommandPool&) = default;
    CommandPool& operator=(const CommandPool&) = default;

private:
    static std::unique_ptr<CommandPool> m_instance;

    std::map<std::string, Callable*> m_commands;
};

#endif
