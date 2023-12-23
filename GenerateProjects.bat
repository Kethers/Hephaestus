call xmake f --solution_name=Hephaestus
call xmake project -k vsxmake

IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)

call xmake f --solution_name=Sandbox
call xmake project -k vsxmake

IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)