cmake_minimum_required(VERSION 2.8.11)

set(THIRD_PARTY_INCLUDES "")
set(BUILD_TESTS OFF)

#adding cpprest
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/cpprest/Release)
set(CASABLANCA_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party/cpprest/Release/include)
set(CASABLANCA_LIBRARY ${Casablanca_LIBRARIES})
set(THIRD_PARTY_INCLUDES
        ${THIRD_PARTY_INCLUDES}
        ${CASABLANCA_INCLUDE_DIR})

#adding azure-storage-cpp
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/azure-storage-cpp/Microsoft.WindowsAzure.Storage)
set(AZURESTORAGE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party/azure-storage-cpp/Microsoft.WindowsAzure.Storage/includes/)
set(THIRD_PARTY_INCLUDES
        ${THIRD_PARTY_INCLUDES}
        ${AZURESTORAGE_INCLUDE_DIR})

#adding cxxopts
set(CXXOPTS_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party/cxxopts/include/)
set(THIRD_PARTY_INCLUDES
        ${THIRD_PARTY_INCLUDES}
        ${CXXOPTS_INCLUDE_DIR})

#adding json
set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party/json/include/)
set(THIRD_PARTY_INCLUDES
        ${THIRD_PARTY_INCLUDES}
        ${JSON_INCLUDE_DIR})

#app
file (GLOB_RECURSE APP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
add_executable (app ${APP_SOURCES})

target_compile_features(app PUBLIC cxx_std_17)
target_include_directories (app PUBLIC ${THIRD_PARTY_INCLUDES})
target_link_libraries(app azurestorage stdc++fs)
