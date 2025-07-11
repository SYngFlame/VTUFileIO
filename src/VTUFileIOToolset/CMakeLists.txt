set(CMAKE_AUTOMOC ON) 
set(CMAKE_INCLUDE_CURRENT_DIR ON) 

# directories
include_directories(
    ${LIBS_QT5_ROOT}/include
    ${LIBS_QT5_ROOT}/include/QtCore
    ${LIBS_QT5_ROOT}/include/QtGui
    ${LIBS_QT5_ROOT}/include/QtWidgets
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
add_library(VTUFileIOToolset SHARED
    ${TARGET_SRC}
    ${HEADERS_MOC}
    ${RESOUCES_RCC}
)

# compiler settings
set_property(TARGET VTUFileIOToolset
    PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS _CRT_NON_CONFORMING_SWPRINTFS
)

set_target_properties(VTUFileIOToolset PROPERTIES LINK_FLAGS /INCLUDE:"__tcmalloc")



add_definitions(
    -DUNICODE
    -D_UNICODE
    -DQT_NO_DEBUG
)

set_target_properties(VTUFileIOToolset PROPERTIES
    OUTPUT_NAME "SAM.Pre.VTUFileIOToolset"
)

# linker settings
set_target_properties(VTUFileIOToolset PROPERTIES
    SUFFIX ".dll")

target_link_libraries(VTUFileIOToolset
    Qt5Core
    OrientBasicContainers
    OrientBasicUtilities
    OrientBasicCoreUtilities
    OrientBasicPrimtives
    OrientPythonInterfaces
    Qt5Core.lib
    Qt5Widgets.lib
    Qt5Gui.lib
    OrientBasicPrimtives.lib
    SAMIngQtSAM.lib
    SAMGui.lib
    libtcmalloc_minimal

)


add_custom_command(TARGET VTUFileIOToolset POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:VTUFileIOToolset>
    ${LIBS_SAM_ROOT}/Release/FilePlugin/SAM.Pre.VTUFileIOToolset.dll
)