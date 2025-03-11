#if defined(WIN32) || defined(__WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_)

#include <windows.h>

long double get_current_time() {
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (long double)t.QuadPart/(long double)f.QuadPart;
}

#else

#include <sys/time.h>
#include <sys/resource.h>

long double get_current_time() {
    struct timeval t;
    gettimeofday(&t, 0);
    return (long double) t.tv_sec + (long double) t.tv_usec*1e-6;
}

#endif
