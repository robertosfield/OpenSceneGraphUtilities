set(SOURCES main.cpp)

add_executable(strip_custom_nodes ${SOURCES})
target_include_directories(strip_custom_nodes PRIVATE ${OSG_INCLUDE_DIR} ${osgEarth_INCLUDE_DIRS})
target_link_libraries(strip_custom_nodes ${OSGEARTH_LIBRARY} ${osgEarth_LIBRARIES} ${OSGDB_LIBRARIES} ${OSG_LIBRARIES} ${OPENTHREADS_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${OPENGL_LIBRARY} ${DL_LIBRARY})
