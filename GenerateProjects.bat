@REM call xmake f --solution_name=Hephaestus
call xmake project -k vsxmake

IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)

@REM call xmake f --solution_name=Sandbox
@REM call xmake project -k vsxmake

@REM IF %ERRORLEVEL% NEQ 0 (
@REM   PAUSE
@REM )