# This is to make test_config.h visible
include_directories("${CMAKE_BINARY_DIR}")

ign_get_sources(tests)

# FIXME the mesh test does not work
list(REMOVE_ITEM tests mesh.cc)

ign_build_tests(
  TYPE INTEGRATION
  SOURCES ${tests}
  INCLUDE_DIRS
      ${PROJECT_SOURCE_DIR}/av/include
      ${PROJECT_SOURCE_DIR}/graphics/include
      ${PROJECT_SOURCE_DIR}/profiler/include
      ${PROJECT_SOURCE_DIR}/events/include)

if(TARGET INTEGRATION_plugin)
  # We add this dependency to make sure that DummyPlugins gets generated
  # before INTEGRATION_plugin so that its auto-generated header is available.
  # We do not want to link INTEGRATION_plugin to the DummyPlugins library.
  add_dependencies(INTEGRATION_plugin IGNDummyPlugins)
endif()

if(TARGET INTEGRATION_mesh_loader_locale)
  add_dependencies(INTEGRATION_mesh_loader_locale
     ignition-common${PROJECT_VERSION_MAJOR}-graphics )
  target_include_directories(INTEGRATION_mesh_loader_locale PRIVATE
    ${ignition-math${IGN_MATH_VER}_INCLUDE_DIRS})
  target_link_libraries(INTEGRATION_mesh_loader_locale
      ignition-common${PROJECT_VERSION_MAJOR}-graphics)
endif()
