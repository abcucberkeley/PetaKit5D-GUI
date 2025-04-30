Unicode True

!include LogicLib.nsh
!define APP_NAME "PetaKit5D-GUI"
!define APP_EXE "PetaKit5D-GUI.exe"
!define RUNTIME_ZIP_URL "https://ssd.mathworks.com/supportfiles/downloads/R2024b/Release/6/deployment_files/installer/complete/win64/MATLAB_Runtime_R2024b_Update_6_win64.zip"
!define TEMP_DIR "C:\temp\matlabRuntimeTmp"
!define TEMP_DIR_D "C:\\temp\\matlabRuntimeTmp"

Name "${APP_NAME}"
OutFile "${APP_NAME}_windows_setup.exe"
InstallDir "C:\Program Files\${APP_NAME}"
RequestExecutionLevel admin

Section
InitPluginsDir
SetOutPath $PLUGINSDIR

File /r "C:\Users\matt\Desktop\PetaKit5D-GUI_releases\jenkins\PetaKit5D-GUI"

; Run the PowerShell command and capture the exit code
nsExec::Exec 'powershell "exit [int]([Environment]::GetEnvironmentVariable(\"PATH\", \"Machine\").Split(\";\")[0] -eq \"C:\Program Files\MATLAB\MATLAB Runtime\R2024b\runtime\win64\")"' $0 SW_HIDE
Pop $0 ; Get the exit code

; Check the exit code
${If} $0 == 1
    DetailPrint "Matlab Runtime found on the path"
${Else}
    DetailPrint "Matlab Runtime not found as the first path. Adding it"
    nsExec::Exec 'powershell "setx -m PATH \"C:\Program Files\MATLAB\MATLAB Runtime\R2024b\runtime\win64;$env:path\""'
${EndIf}

IfFileExists "C:\Program Files\MATLAB\MATLAB Runtime\R2024b\VersionInfo.xml" skip_runtime install_runtime 
install_runtime:
CreateDirectory ${TEMP_DIR}

; Download the Matlab Runtime
NSISdl::download "${RUNTIME_ZIP_URL}" "${TEMP_DIR}\matlabRuntime.zip"
Pop $R0 ; Get the results
DetailPrint "Download result: $R0"

CreateDirectory C:\temp\matlabRuntimeTmp\matlabRuntimeTmp
DetailPrint "Extracting the Matlab Runtime. This may take a few minutes..."
nsExec::Exec 'tar -xf "C:\\temp\\matlabRuntimeTmp\\matlabRuntime.zip" -C "C:\\temp\\matlabRuntimeTmp\\matlabRuntimeTmp"' $0 SW_HIDE
Pop $0 ; Get the result of Unzip
StrCmp $0 "success" okRuntime
  DetailPrint "$0" ;print error message to log
okRuntime:

DetailPrint "Installing the Matlab Runtime. This may take a few minutes..."
nsExec::Exec 'powershell "&\"C:\\Temp\\matlabRuntimeTmp\\matlabRuntimeTmp\\setup\" -agreeToLicense yes -destinationFolder \"C:\\Program Files\\MATLAB\\MATLAB Runtime\" | Out-Null"' $0 SW_HIDE
Pop $0
StrCmp $0 "success" okRuntimeS
  DetailPrint "$0" ;print error message to log
okRuntimeS:

RMDir /r "${TEMP_DIR}"

skip_runtime:
DetailPrint "Installing PetaKit5D-GUI files..."
CopyFiles /Silent "$PLUGINSDIR\PetaKit5D-GUI" "$InstDir"

SectionEnd

Section "Install"
SetOutPath $INSTDIR
CreateShortcut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${APP_EXE}"
WriteUninstaller "$INSTDIR\uninstall_PetaKit5D-GUI.exe"
SectionEnd

Section "Uninstall"
Delete "$DESKTOP\${APP_NAME}.lnk"
Delete "$INSTDIR\${APP_EXE}"
RMDir /r "$INSTDIR"
RMDir "$INSTDIR"
SectionEnd
