set PROJECT=ProjectEmbeddedSystems
set BIN=C:\Users\mayna\Tools\bin
set WORKSPACE=C:\Users\mayna\Tools\workspace


start %BIN%\tsim-eval\tsim\win64\tsim-leon3.exe -c %WORKSPACE%\%PROJECT%\Tests\tsim_init
call %BIN%\bcc-2.2.0-gcc\bin\sparc-gaisler-elf-gdb %WORKSPACE%\%PROJECT%\Debug\%PROJECT% -d %WORKSPACE%\%PROJECT%\src -batch -x %WORKSPACE%\%PROJECT%\Tests\gdb_batch_001.txt