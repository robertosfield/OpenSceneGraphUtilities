cmake_minimum_required(VERSION 3.7)

project(osgutilities
    VERSION 0.0.0
    DESCRIPTION "OpenSceneGraph utilities"
    LANGUAGES CXX
)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

# Find OpenSceneGraph packages for reference
# set prefrence for using modern OpenGL library.
find_package(OpenSceneGraph REQUIRED COMPONENTS osgDB osgTerrain osgUtil osgGA osgViewer )

find_package(osgEarth)


if(WIN32)
    set(OPENGL_LIBRARY ${OPENGL_gl_LIBRARY})
else()
    set(OPENGL_LIBRARY OpenGL::GL)
endif()

find_package(Threads)

if (UNIX)
    find_library(DL_LIBRARY dl)
endif()


add_subdirectory(applications)
