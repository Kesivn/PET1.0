# CMake generated Testfile for 
# Source directory: E:/毕业设计/PET1.0
# Build directory: E:/毕业设计/PET1.0/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[PET_SmokeTest]=] "E:/毕业设计/PET1.0/build/Debug/pet_smoke_test.exe")
  set_tests_properties([=[PET_SmokeTest]=] PROPERTIES  _BACKTRACE_TRIPLES "E:/毕业设计/PET1.0/CMakeLists.txt;60;add_test;E:/毕业设计/PET1.0/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[PET_SmokeTest]=] "E:/毕业设计/PET1.0/build/Release/pet_smoke_test.exe")
  set_tests_properties([=[PET_SmokeTest]=] PROPERTIES  _BACKTRACE_TRIPLES "E:/毕业设计/PET1.0/CMakeLists.txt;60;add_test;E:/毕业设计/PET1.0/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[PET_SmokeTest]=] "E:/毕业设计/PET1.0/build/MinSizeRel/pet_smoke_test.exe")
  set_tests_properties([=[PET_SmokeTest]=] PROPERTIES  _BACKTRACE_TRIPLES "E:/毕业设计/PET1.0/CMakeLists.txt;60;add_test;E:/毕业设计/PET1.0/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[PET_SmokeTest]=] "E:/毕业设计/PET1.0/build/RelWithDebInfo/pet_smoke_test.exe")
  set_tests_properties([=[PET_SmokeTest]=] PROPERTIES  _BACKTRACE_TRIPLES "E:/毕业设计/PET1.0/CMakeLists.txt;60;add_test;E:/毕业设计/PET1.0/CMakeLists.txt;0;")
else()
  add_test([=[PET_SmokeTest]=] NOT_AVAILABLE)
endif()
