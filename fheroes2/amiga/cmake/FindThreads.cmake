# FindThreads.cmake override for AmigaOS 3.x
# Threading is provided by SDL2 (Exec Tasks), not pthreads.
# Mark as found but don't link any library.

set(Threads_FOUND TRUE)
set(CMAKE_THREAD_LIBS_INIT "")
set(CMAKE_USE_PTHREADS_INIT FALSE)

if(NOT TARGET Threads::Threads)
    add_library(Threads::Threads INTERFACE IMPORTED)
endif()
