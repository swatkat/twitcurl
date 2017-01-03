project(twitcurl)
cmake_minimum_required(VERSION 2.8)

get_filename_component(TWITCURL_ROOT "./" ABSOLUTE)
set(CURL_PATH ${TWITCURL_ROOT})
set(CURL_LIB ${CURL_PATH}/lib/libcurl.lib)
set(CURL_DLL_PATH ${CURL_PATH}/dlls/libcurl.dll)

set(TWITCURL_LIBS 
    ${PROJECT_NAME}
    ${CURL_LIB}
    CACHE LIST "Set the list of lib paths for twitcurl")

set(TWITCURL_INC
    ${CURL_PATH}/include 
    ${TWITCURL_ROOT}
    CACHE LIST "Set the list of include paths for twitcurl")

set(TWITCURL_SRC
    base64.cpp
    HMAC_SHA1.cpp
    oauthlib.cpp
    SHA1.cpp
    urlencode.cpp
    twitcurl.cpp
    )

set(TWITCURL_HEADERS
    base64.h
    HMAC_SHA1.h
    oauthlib.h
    SHA1.h
    urlencode.h
    twitcurl.h
    )

include_directories(
    ${TWITCURL_INC}
    )

add_library(${PROJECT_NAME} STATIC ${TWITCURL_SRC} ${TWITCURL_HEADERS})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )
