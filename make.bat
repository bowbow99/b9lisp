@echo off

set PROJECT_FILE=b9lisp.vcxproj

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
if not exist %PROJECT_FILE% (
  call :PREBUILD
)
msbuild /nologo %PROJECT_FILE%
exit /b

:RUN
if not exist "bin\b9lisp.exe" (
  call :BUILD
)
bin\b9lisp.exe
exit /b

:CLEAN
if exist %PROJECT_FILE% (
  msbuild /nologo /target:Clean %PROJECT_FILE%
)
if exist "bin" (
  rmdir /s /q bin
)
exit /b

:END
