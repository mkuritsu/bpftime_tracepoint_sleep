cmake_minimum_required(VERSION 3.14)
project(prototype LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# FetchContent for dependencies
include(FetchContent)

# Fetch llvmbpf library
# FetchContent_Declare(
#     llvmbpf
#     GIT_REPOSITORY https://github.com/eunomia-bpf/llvmbpf.git
#     GIT_TAG        main
# )
# FetchContent_MakeAvailable(llvmbpf)

FetchContent_Declare(
    bpftime
    GIT_REPOSITORY https://github.com/eunomia-bpf/bpftime.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(bpftime)

# Find FridaGum library path
set(FRIDA_GUM_INSTALL_DIR ${bpftime_BINARY_DIR}/FridaGum-prefix/src/FridaGum)

# Main executable
add_library(${PROJECT_NAME} SHARED src/agent.cpp)

# Link against bpftime runtime
target_link_libraries(${PROJECT_NAME} PRIVATE
    runtime
    bpftime_vm
    bpftime_llvm_vm
    llvmbpf_vm
    spdlog::spdlog
    bpftime_base_attach_impl
    bpftime_frida_uprobe_attach_impl
    bpftime_syscall_trace_attach_impl
    bpftime-object
    ${FRIDA_GUM_INSTALL_DIR}/libfrida-gum.a
    -lpthread
    -lm
    -ldl
    -lz
    -lelf
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${bpftime_SOURCE_DIR}/runtime/include
    ${bpftime_SOURCE_DIR}/runtime/src
    ${bpftime_SOURCE_DIR}/runtime/object
    ${bpftime_SOURCE_DIR}/vm/include
    ${bpftime_SOURCE_DIR}/vm/llvm-jit/include
    ${bpftime_SOURCE_DIR}/vm/compat/llvm-vm
    ${bpftime_SOURCE_DIR}/vm/vm-core
    ${bpftime_SOURCE_DIR}/third_party
    ${bpftime_SOURCE_DIR}/attach/base_attach_impl
    ${bpftime_SOURCE_DIR}/attach/frida_uprobe_attach_impl/include
    ${bpftime_SOURCE_DIR}/attach/syscall_trace_attach_impl/include
    ${SPDLOG_INCLUDE}
)
