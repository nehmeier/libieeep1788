add_executable(basic basic.cpp ${HEADER_FILES})
target_link_libraries(basic ${MPFR_LIB})

add_executable(boolFunc boolFunc.cpp ${HEADER_FILES})
target_link_libraries(boolFunc ${MPFR_LIB})

add_executable(elementaryFunc elementaryFunc.cpp ${HEADER_FILES})
target_link_libraries(elementaryFunc ${MPFR_LIB})

