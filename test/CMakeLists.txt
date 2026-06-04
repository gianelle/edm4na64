# SPDX-License-Identifier: Apache-2.0

IF(NOT BUILD_TESTING)
  RETURN()
ENDIF()

set(sio_libs podio::podioSioIO podio::podioIO)
set(root_libs podio::podioRootIO)

function(set_test_env _testname)
  set_property(TEST ${_testname} APPEND PROPERTY ENVIRONMENT
      LD_LIBRARY_PATH=$<TARGET_FILE_DIR:edm4na64>:$<TARGET_FILE_DIR:EDM4HEP::edm4hep>:$<TARGET_FILE_DIR:podio::podio>:$<$<TARGET_EXISTS:EDM4HEP::edm4hepRDF>:$<TARGET_FILE_DIR:EDM4HEP::edm4hepRDF>:>$<TARGET_FILE_DIR:ROOT::Core>:$ENV{LD_LIBRARY_PATH}
      ROOT_INCLUDE_PATH=${PROJECT_SOURCE_DIR}/utils/include:$ENV{ROOT_INCLUDE_PATH}
  )
  set_tests_properties(${_testname} PROPERTIES
    FAIL_REGULAR_EXPRESSION "[^a-z]Error;ERROR;error;Failed"
    )
endfunction()

add_executable(write_events write_events.cc)
target_include_directories(write_events PUBLIC ${PROJECT_SOURCE_DIR}/edm4hep )
target_link_libraries(write_events edm4na64 edm4na64::edm4na64Dict EDM4HEP::edm4hep "${sio_libs}" "${root_libs}" podio::podioDict podio::podioRootIODict)
add_test(NAME write_events COMMAND write_events)
set_test_env(write_events)

add_executable(read_events read_events.cc)
target_include_directories(read_events PUBLIC ${PROJECT_SOURCE_DIR}/edm4hep )
target_link_libraries(read_events edm4na64 EDM4HEP::edm4hep podio::podioRootIO podio::podioDict podio::podioRootIODict)
add_test(NAME read_events COMMAND read_events)
  set_property(TEST read_events PROPERTY
    DEPENDS write_events
    )
set_test_env(read_events)
