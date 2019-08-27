#include "commands.hpp"

std::unique_ptr<CommandPool> CommandPool::m_instance = nullptr;

CommandPool& CommandPool::getInstance()
{
    if (m_instance == nullptr)
        m_instance = std::unique_ptr<CommandPool>(new CommandPool);
    return *m_instance;
}

void CommandPool::registerCommand(Callable* ptr)
{
    if (ptr != nullptr)
        m_commands[ptr->toString()] = ptr;
}

Callable* CommandPool::findCommand(const std::string& name)
{
    if (m_commands.find(name) != m_commands.end())
        return m_commands[name];
    return nullptr;
}
