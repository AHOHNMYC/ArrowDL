@echo off
:: Copyright 2019-present Sébastien Vavassori. All rights reserved.
:: Use of this source code is governed by a LGPL license that can be
:: found in the LICENSE file.

SET QUIET=0
:loop
IF NOT "%1"=="" (
    IF "%1"=="-quiet" (
        SET QUIET=1
        SHIFT
    )
    SHIFT
    GOTO :loop
)

ECHO *************************************************
ECHO                  Down Right Now
ECHO *************************************************
ECHO.

ECHO.
ECHO Deleting Chrome Registry...
ECHO ---------------------------------
REG DELETE "HKCU\Software\Google\Chrome\NativeMessagingHosts\com.setvisible.downrightnow" /f

ECHO.
ECHO Deleting Firefox Registry...
ECHO ---------------------------------
REG DELETE "HKCU\SOFTWARE\Mozilla\NativeMessagingHosts\DownRightNow" /f

ECHO.
ECHO Deleting Waterfox Registry...
ECHO ---------------------------------
REG DELETE "HKCU\SOFTWARE\Waterfox\NativeMessagingHosts\DownRightNow" /f

ECHO.
ECHO Deleting Thunderbird Registry...
ECHO ---------------------------------
REG DELETE "HKCU\SOFTWARE\Thunderbird\NativeMessagingHosts\DownRightNow" /f

ECHO.
ECHO ^>^>^> Done! ^<^<^<
ECHO.

IF NOT "%QUIET%"=="1" (
    TIMEOUT /T 10
)
