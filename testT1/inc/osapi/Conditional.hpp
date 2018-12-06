#ifndef OSAPI_COND_HPP
#define OSAPI_COND_HPP

#include <osapi/Utility.hpp>

#if defined(OS_WINX86)
#include "osapi/winx86/Conditional.hpp"
#elif defined(OS_LINUX)
#include "osapi/linux/Conditional.hpp"
#elif defined(OS_FREERTOS)
#include "osapi/freertos/Conditional.hpp"
#else
#error "No known OS defined"
#endif




#endif
