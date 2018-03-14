#ifndef RETURN_HPP
#define RETURN_HPP

#include <stdexcept>

#include "value.hpp"

struct Return : public std::runtime_error
{
        Return(Value v) : runtime_error("Return"), m_value(v)  {}

        virtual ~Return() throw() {}

        Value m_value;
};
#endif

