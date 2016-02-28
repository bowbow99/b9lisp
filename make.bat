@echo off

if "%1" == "clean" (
  call :CLEAN
  goto END
)

if "%1" == "run" (
  call :BUILD
  call :RUN
  goto :END
)

call :BUILD
goto :END


:PREBUILD
premake5 vs2013
exit /b

:BUILD
if not exist "build/b9lisp.vcxproj" (
  call :PREBUILD
)
msbuild /nologo build\b9lisp.vcxproj
exit /b

:RUN
if not exist "bin\b9lisp.exe" (
  call :BUILD
)
bin\b9lisp.exe
exit /b

:CLEAN
if exist "build" (
  msbuild /nologo /target:Clean build\b9lisp.vcxproj
  rmdir /s /q build
)
if exist "bin" (
  rmdir /s /q bin
)
exit /b

:END
