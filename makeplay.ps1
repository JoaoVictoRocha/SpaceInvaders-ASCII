Set-Location "C:\Users\joaov\SpaceInvaders"

g++ -g --std=c++17 -o game.exe src/ASCII_Engine/Core/*.cpp src/ASCII_Engine/utils/*.cpp src/ASCII_Engine/*.cpp src/*.cpp

Write-Host "Compilado"

Start-Process "powershell.exe" -ArgumentList "./game.exe"

Start-Process "utils/Display_Control.ahk"