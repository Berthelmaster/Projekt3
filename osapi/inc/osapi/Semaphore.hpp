#ifndef OSAPI_SEMAPHORE_HPP
#define OSAPI_SEMAPHORE_HPP

#include <osapi/Utility.hpp>
#include <osapi/SemaphoreError.hpp>


#if defined(OS_WINX86)
#include "osapi/winx86/Semaphore.hpp"
#elif defined(OS_LINUX)
#include "osapi/linux/Semaphore.hpp"
#elif defined(OS_FREERTOS)
#include "osapi/freertos/Semaphore.hpp"
#else
#error "No known OS defined"
#endif



#endif
