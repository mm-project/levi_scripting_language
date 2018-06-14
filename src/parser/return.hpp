#ifndef RETURN_HPP
#define RETURN_HPP

#include <stdexcept>

#include "value.hpp"

/// @class Return
struct Return : public std::runtime_error
{
        /// @brief Constructor
        Return(Value v) : runtime_error("Return"), m_value(v)
        {}

        /// @brief Destructor
        virtual ~Return() throw() {}

        Value m_value;
};
#endif

