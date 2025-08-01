set(CMAKE_AUTOMOC ON) 
set(CMAKE_INCLUDE_CURRENT_DIR ON) 

# directories
include_directories(
    ${LIBS_QT5_ROOT}/include
    ${LIBS_QT5_ROOT}/include/QtCore
    ${LIBS_PYTHON_ROOT}/include
    ${LIBS_OC_ROOT}/include
    ${LIBS_SAMSDK_ROOT}/include
    ${LIBS_SAMSDK_ROOT}/include/guiProject

    ${LIBS_VTK_ROOT}/include
)
  
link_directories(
    ${LIBS_QT5_ROOT}/lib
    ${LIBS_PYTHON_ROOT}/libs
    ${LIBS_OC_ROOT}/lib
	${LIBS_SAMSDK_ROOT}/libs
	${PROJECT_SOURCE_DIR}/lib
    ${LIBS_TCMALLOC_ROOT}
    ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}

    ${LIBS_VTK_ROOT}/lib
)

# source list
file(GLOB TARGET_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.T"
    )
     
# Moc Qt headers
set(HEADERS
)

QT5_WRAP_CPP(HEADERS_MOC ${HEADERS})
QT5_ADD_RESOURCES(RESOUCES_RCC ${RESOUCES})


# add filters
source_group("Generated Files" FILES
    ${HEADERS_MOC}
)

# dynamic library
add_library(VTUFileIO SHARED
    ${TARGET_SRC}
    ${HEADERS_MOC}
    ${RESOUCES_RCC}
)

# compiler settings
set_property(TARGET VTUFileIO
    PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS _CRT_NON_CONFORMING_SWPRINTFS
)

set_target_properties(VTUFileIO PROPERTIES LINK_FLAGS /INCLUDE:"__tcmalloc")



add_definitions(
    -DUNICODE
    -D_UNICODE
)

# linker settings
set_target_properties(VTUFileIO PROPERTIES
    SUFFIX ".pyd")

target_link_libraries(VTUFileIO
    OrientBasicUtilities
    OrientBasicCoreUtilities
    OrientBasicPrimtives
    OrientPythonInterfaces
    SAMPythonModuleConfiguration
    SAMCommonCommand
    SAMKernelAttributesInterfaceObjects
    SAMSessionCommonDefs
    SAMSceneGraph
    SAMPrimaryObjects
    SAMKernel
    Qt5Core.lib
    Qt5Widgets.lib
    Qt5Gui.lib
    ${LIBS_PYTHON_ROOT}/libs/*
    ${LIBS_OC_ROOT}/lib/*
	${LIBS_SAMSDK_ROOT}/libs/*
	${PROJECT_SOURCE_DIR}/lib/*
    ${LIBS_VTK_ROOT}/lib/*
    libtcmalloc_minimal.lib
)