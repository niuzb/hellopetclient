@echo

cls

set PROJ_DIR=%cd%
set ONLINE_PROTO_DIR=%PROJ_DIR%\proto

set NETWORK_DIR=%PROJ_DIR%\Classes\NetWork
set SERVER_DIR=%PROJ_DIR%\Classes\Server

cd %PROJ_DIR%
copy %ONLINE_PROTO_DIR%\*.proto %NETWORK_DIR%\proto\*.proto
copy %ONLINE_PROTO_DIR%\*.proto %SERVER_DIR%\proto\*.proto

%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\cs_core.proto 
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\cs_basic.proto  
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\cs_battle.proto  
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\errcode.proto
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\db.proto
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\cs_config.proto




%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto -o%PROJ_DIR%\Resources\Script\Pbc\cs_core.bin  %NETWORK_DIR%\proto\cs_core.proto 
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto -o%PROJ_DIR%\Resources\Script\Pbc\cs_basic.bin  %NETWORK_DIR%\proto\cs_basic.proto  
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto -o%PROJ_DIR%\Resources\Script\Pbc\cs_battle.bin  %NETWORK_DIR%\proto\cs_battle.proto  
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto -o%PROJ_DIR%\Resources\Script\Pbc\errcode.bin  %NETWORK_DIR%\proto\errcode.proto
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto -o%PROJ_DIR%\Resources\Script\Pbc\db.bin  %NETWORK_DIR%\proto\db.proto
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto -o%PROJ_DIR%\Resources\Script\Pbc\cs_config.bin  %NETWORK_DIR%\proto\cs_config.proto

cd %PROJ_DIR%
