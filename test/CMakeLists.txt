cmake_minimum_required(VERSION 3.21)

set(This testTests)

set(Headers
    testFiles/card.h
    testFiles/linkedCard.h
    testFiles/memory.h
    testFiles/game.h
    testFiles/server.h
    testFiles/sendmessages.h
    testFiles/mockSendMessages.h
    testFiles/qimage.h
    testFiles/receivemessages.h
    testFiles/mockReceiveMessages.h
)

set(Sources
    test.cpp
    testFiles/card.cpp
    testFiles/linkedCard.cpp
    testFiles/memory.cpp
    testFiles/game.cpp
    testFiles/server.cpp
    testFiles/sendmessages.cpp
    testFiles/mockSendMessages.cpp
    testFiles/qimage.cpp
    testFiles/receivemessages.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC 
    gtest_main
    gmock_main
)

add_test(
    NAME ${This}
    COMMAND ${This}
)