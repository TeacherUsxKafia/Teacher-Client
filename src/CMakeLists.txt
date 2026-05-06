file(GLOB src
    "*.cpp"
    "../utils/*.cpp"
)

# Automated cleanup: Since we deleted AccountManager and LobbySeeker files,
# file(GLOB) will no longer try to compile them.

add_definitions(
    -DCLIENT_VERSION_STRING="${CLIENT_VERSION_STRING}"
    -DCLIENT_VERSION_STRING_MIN="${CLIENT_VERSION_STRING_MIN}"
    -DCLIENT_MAJOR_VERSION=${CLIENT_MAJOR_VERSION}
    -DCLIENT_MINOR_VERSION=${CLIENT_MINOR_VERSION}
    -DCLIENT_PATCH_VERSION=${CLIENT_PATCH_VERSION}
    -DWH_USE_WININET
)

add_executable(Client WIN32 ${src})
target_sources(Client PRIVATE Resource.rc)

# Essential includes only - Removed Discord to boost performance
target_include_directories(Client PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${RAPIDJSON}/include
    ${URIPARSER}/include
    ${SEMVER}/include
    ${WEBVIEW2}/build/native/include
    ${WIL}/include
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(WEBVIEW2_ARCH "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    SET(WEBVIEW2_ARCH "x86")
endif()

# Linking only what is needed for the core engine and low latency
target_link_libraries(Client 
    crypt32 
    winhttp 
    uriparser 
    ${WEBVIEW2}/build/native/${WEBVIEW2_ARCH}/WebView2LoaderStatic.lib
)

target_compile_features(Client PUBLIC cxx_std_20)
set_target_properties(Client PROPERTIES CXX_EXTENSIONS OFF)