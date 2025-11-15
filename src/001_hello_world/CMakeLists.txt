# Get the directory name as target name
get_filename_component(target_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Find all .cpp files in current directory
file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Check for include directory and add it
set(include_dirs "")
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    list(APPEND include_dirs "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif()

# Add LLVM include path
list(APPEND include_dirs "${LLVM_INCLUDE_DIR}")

# Create executable
if(sources)
    add_executable(${target_name} ${sources})
    target_include_directories(${target_name} PRIVATE ${include_dirs})
endif()
