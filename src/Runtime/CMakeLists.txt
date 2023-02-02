set(TARGET_NAME ${PROJECT_NAME}Runtime)

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${PROJECT_NAME})

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")
target_compile_definitions(${TARGET_NAME} PUBLIC "CGAL_USE_BASIC_VIEWER")

# Link dependencies    
target_link_libraries(${TARGET_NAME} PUBLIC
Qt5::Core
Qt5::Gui
Qt5::Widgets
Qt5::OpenGL
CGAL::CGAL CGAL::Data
          )


if(CGAL_Qt5_FOUND)
#link it with the required CGAL libraries
target_link_libraries(${TARGET_NAME} PUBLIC CGAL::CGAL_Basic_viewer)
endif()

target_include_directories(
  ${TARGET_NAME} 
  PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)
