add_subdirectory(init)

# Object library type is used to prevent compiler from removing unit test functions from the binary.
add_library(apposal-tests OBJECT EXCLUDE_FROM_ALL
    appMain.cpp
    Error.cpp
    Mutex.cpp
    MutexObject.cpp
    ScopedLock.cpp
    Semaphore.cpp
    SemaphoreObject.cpp
    Thread.cpp
    ThreadObject.cpp
    time.cpp
    Timeout.cpp
)

target_include_directories(apposal-tests
    PRIVATE .
)

target_compile_features(apposal-tests
    PRIVATE cxx_std_17
)

conan_get(REQUIRES catch2/2.12.1)
find_package(Catch2 REQUIRED)

if (PLATFORM STREQUAL freertos-arm)
    # This is required, because FreeRTOS doesn't support signals or exceptions.
    target_compile_definitions(Catch2::Catch2 INTERFACE CATCH_CONFIG_NO_POSIX_SIGNALS CATCH_CONFIG_DISABLE_EXCEPTIONS)
endif ()

target_link_libraries(apposal-tests
    PUBLIC platform-init
    PRIVATE Catch2::Catch2 osal::c osal::cpp
)

# This is required to selectively run Catch2 tests using tags on platforms, where cmd line arguments are not available.
if (DEFINED TEST_TAGS)
    target_compile_definitions(apposal-tests
        PRIVATE TEST_TAGS="${TEST_TAGS}"
    )
endif ()
