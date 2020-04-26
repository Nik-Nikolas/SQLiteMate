cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME SQLiteMate)
project(${PROJECT_NAME})

# setup cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# exe
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/SQLiteBroker.cpp
        src/sqlite3/sqlite3.c
        include/DefaultNames.h)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

# threads for sqlite:
# pthread_mutexattr_init
# pthread_mutexattr_settype
# pthread_mutexattr_destroy
# pthreadMutexTry pthread_
# mutex_trylock
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

# for sqlite functions:
# unixDlOpen
# unixDlError
# unixDlSym
# unixDlClose
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})

# install
include(GNUInstallDirs)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-export
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT ${PROJECT_NAME}-export
        FILE
        ${PROJECT_NAME}-config.cmake
        NAMESPACE
        ${PROJECT_NAME}::
        DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})