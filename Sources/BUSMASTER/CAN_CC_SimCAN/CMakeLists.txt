set(sources
  CAN_CC_SimCAN.cpp
  CANRegAnalysis.cpp
  ChangeRegisters.cpp
  HardwareListing.cpp
  ../Application/MultiLanguage.cpp)

set(headers
  CAN_CC_SimCAN.h
  CAN_CC_SimCAN_Extern.h
  CAN_CC_SimCAN_Resource.h
  CAN_CC_SimCAN_stdafx.h
  ChangeRegDefines.h
  ChangeRegisters.h
  ContrConfigPeakUsbDefs.h
  HardwareListing.h
  ../Application/MultiLanguage.h)

set(resources
  CAN_CC_SimCAN.rc)

add_library(CAN_CC_SimCAN SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_USRDLL)

# linker options
set_target_properties(CAN_CC_SimCAN PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(CAN_CC_SimCAN
  Advapi32
  DataTypes
  Utils)

# installer options
add_custom_command(
  TARGET CAN_CC_SimCAN
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:CAN_CC_SimCAN> ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/)
