:: build.bat
@echo off
call loadenv.bat
echo %sdl2_lib_path_x86%
echo %sdl2_lib_path_x64%
echo %sdl2_include_path%
echo %msvcl_build_path%
echo %msvcl_libs%
echo %opencl_lib_path_x64%
echo %tcc_winapi_include_path%
echo %tcc_lib_path%
echo %llvm_path%

set PATH=%llvm_path%;%PATH%

rem if not exist build\clang_x64 mkdir build\clang_x64 
rem pushd build\clang_x64
rem clang-cl -target x86_64-pc-windows-msvc ^
rem   /I"%opencl_include_path%" ^
rem   /O2 ^
rem   /GS- ^
rem   /arch:AVX2 ^
rem   /W4 -Xclang -std=c89 /Tc ^
rem   ..\..\win32_heap_threadctx_503.c ^
rem   /link ^
rem   /LIBPATH:"%opencl_lib_path_x64%" ^
rem   OpenCL.lib kernel32.lib user32.lib gdi32.lib ^
rem   /MACHINE:X64 ^
rem   /NODEFAULTLIB ^
rem   /ENTRY:win32_main_entry ^
rem   /SUBSYSTEM:WINDOWS ^
rem   /OUT:win32_heap_threadctx_503.exe
rem popd

rem call %msvcl_build_path%\vcvarsall.bat x64
rem if not exist build\msvcl_x64 mkdir build\msvcl_x64 
rem pushd build\msvcl_x64
rem cl ^
rem   /I"%opencl_include_path%" ^
rem   /O2 ^
rem   /GS- ^
rem   /arch:AVX2 ^
rem   /W4 /permissive- /Tc ^
rem   ..\..\win32_heap_threadctx_503.c ^
rem   /link ^
rem   /LIBPATH:"%opencl_lib_path_x64%" ^
rem   OpenCL.lib kernel32.lib user32.lib gdi32.lib ^
rem   /MACHINE:X64 ^
rem   /NODEFAULTLIB ^
rem   /ENTRY:win32_main_entry ^
rem   /SUBSYSTEM:WINDOWS ^
rem   /OUT:win32_heap_threadctx_503.exe
rem popd

pause
::/permissive-  Standard conformance mode (Turn this on instead of /Za). It is much smarter and won't break windows.h.
::/GS-  Disables stack security cookies (Required).
::/Oi Enables intrinsics (Helps the compiler replace some CRT calls with CPU instructions).
::/GR-  Disables RTTI (Run-Time Type Information).
::/EHa- Disables C++ Exception Handling.
::/NODEFAULTLIB The "Nuclear Option" that removes the CRT entirely.