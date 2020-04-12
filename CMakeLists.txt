cmake_minimum_required(VERSION 3.15)
project(Simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Simulator main.cpp Command.cpp Command.h OpenServerCommand.cpp OpenServerCommand.h DefineVarCommand.cpp DefineVarCommand.h ConditionCommand.h WhileCommand.cpp WhileCommand.h IfCommand.cpp
        IfCommand.h SleepCommand.cpp SleepCommand.h PrintCommand.cpp PrintCommand.h Var.cpp Var.h ConnectControlClientCommand.cpp ConnectControlClientCommand.h
        Lexer.cpp Lexer.h Parser.cpp Parser.h Variables.cpp Variables.h SleepCommand.cpp SleepCommand.h ShuntingYard.cpp ShuntingYard.h Expression.h EqualCommand.cpp EqualCommand.h ConditionCommand.cpp FuncCommand.cpp FuncCommand.h)
target_link_libraries(${PROJECT_NAME} pthread)