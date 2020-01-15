
set(SOURCES
    src/connection.cpp
    src/function_detail.cpp
    src/signal_impl.cpp
    )

set(HEADERS
    include/bind_weak.h
    include/combiners.h
    include/connection.h
    include/function_detail.h
    include/function.h
    include/msvc_autolink.h
    include/signal_impl.h
    include/signal.h
    include/spin_mutex.h
    include/type_traits.h
    )

add_library(fastsignals SHARED ${SOURCES} ${HEADERS})
target_include_directories(fastsignals INTERFACE "${CMAKE_SOURCE_DIR}")
