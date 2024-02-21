# CMake generated Testfile for 
# Source directory: /home/carlos/Documents/Allocateur_Memoire
# Build directory: /home/carlos/Documents/Allocateur_Memoire/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(AllTestsAllocator "alloctest")
set_tests_properties(AllTestsAllocator PROPERTIES  _BACKTRACE_TRIPLES "/home/carlos/Documents/Allocateur_Memoire/CMakeLists.txt;66;add_test;/home/carlos/Documents/Allocateur_Memoire/CMakeLists.txt;0;")
subdirs("gtest")
