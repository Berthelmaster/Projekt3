#ifndef OSAPI_THREAD_HPP
#define OSAPI_THREAD_HPP

#if defined(OS_WINX86)
#include "osapi/winx86/Thread.hpp"
#elif defined(OS_LINUX)
#include "osapi/linux/Thread.hpp"
#elif defined(OS_FREERTOS)
#include "osapi/freertos/Thread.hpp"
#endif

#endif
