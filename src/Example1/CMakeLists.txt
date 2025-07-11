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
    
)
  
link_directories(
    ${LIBS_QT5_ROOT}/lib
    ${LIBS_PYTHON_ROOT}/libs
    ${LIBS_OC_ROOT}/lib
	${LIBS_SAMSDK_ROOT}/libs
	${PROJECT_SOURCE_DIR}/lib
    ${LIBS_TCMALLOC_ROOT}
    ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
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
add_library(Example1 SHARED
    ${TARGET_SRC}
    ${HEADERS_MOC}
    ${RESOUCES_RCC}
)

# compiler settings
set_property(TARGET Example1
    PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS _CRT_NON_CONFORMING_SWPRINTFS
)

set_target_properties(Example1 PROPERTIES LINK_FLAGS /INCLUDE:"__tcmalloc")



add_definitions(
    -DUNICODE
    -D_UNICODE
)

# linker settings
set_target_properties(Example1 PROPERTIES
    SUFFIX ".pyd")

target_link_libraries(Example1
    Qt5Core.lib
	OrientBasicContainers
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
    libtcmalloc_minimal.lib
)