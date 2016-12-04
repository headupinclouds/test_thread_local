#include "bar.hpp"
#include <iostream> // std::cout
#include <bar_export.h> // BAR_EXPORT

#include <memory>

std::shared_ptr<SomeType<128>> BAR_EXPORT bar()
{
    return std::make_shared<SomeType<128>>();
}


