ADD_EXECUTABLE(lcal term.cpp sum.cpp pot.cpp fac.cpp helpers.cpp lcal.cpp)
TARGET_LINK_LIBRARIES(lcal m)
INSTALL(TARGETS
  lcal
  DESTINATION
  lcal
)
