:: loadenv.bat
@echo off
for /f "usebackq tokens=1,* delims==" %%A in (".example.env") do (
  if not "%%A"=="" if not "%%A:~0,1%"=="#" (
    set "%%A=%%B"
  )
)
