@echo off
if %CONFIGURATION% EQU "" (
  set CONFIGURATION=Debug
)
if "PLATFORM%" EQU "" (
  set PLATFORM=x64
)
set "ANGLE_URL=https://ci.appveyor.com/api/projects/lygstate/angle/artifacts/angle.zip?branch=ms-master"
set "ANGLE_URL_PARAMS=job=Configuration%%3a+%CONFIGURATION%%%3b+Platform%%3a+%PLATFORM%

echo Downloading "%ANGLE_URL%&%ANGLE_URL_PARAMS%"
:: Refer to http://stackoverflow.com/questions/9100099/why-is-curl-truncating-this-query-string
curl -L -o angle.zip "%ANGLE_URL%&%ANGLE_URL_PARAMS%"
