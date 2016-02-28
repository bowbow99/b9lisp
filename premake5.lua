-- premake5.lua for b9lisp

solution "b9lisp"
    configurations { "Debug", "Release" }
    architecture "x64"

project "b9lisp"
    kind "ConsoleApp"
    language "C"

    targetdir "bin"

    files { "src/*.h", "src/*.c" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        flags   { "Symbols" }
        warnings "Extra"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
