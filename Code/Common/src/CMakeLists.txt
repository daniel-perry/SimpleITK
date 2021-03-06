set ( SimpleITKCommonSource
  sitkImage.cxx
  sitkPixelIDValues.cxx
  sitkExceptionObject.cxx
  ${CMAKE_CURRENT_BINARY_DIR}/sitkVersion.cxx
  ../include/Ancillary/hl_md5.cxx
  ../include/Ancillary/hl_sha1.cxx
  )


set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER )
include(${ITK_USE_FILE})

add_library ( SimpleITKCommon ${SimpleITKCommonSource} ${SimpleITKAncillarySource} )
target_link_libraries ( SimpleITKCommon ${ITK_LIBRARIES} )

# Add custom command that will delete java files which need to be rebuilt when changes
# are made to Common
if( WRAP_JAVA )
  add_custom_command(
    TARGET SimpleITKCommon
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND ${CMAKE_COMMAND} -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
  )
endif()
