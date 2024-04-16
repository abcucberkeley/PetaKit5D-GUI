Unicode True

!define APP_NAME "LLSM_Processing_GUI"
!define APP_EXE "LLSM_Processing_GUI.exe"
!define ZIP_URL "https://github.com/abcucberkeley/LLSM_Processing_GUI/releases/download/v1.3.0/developers_only.zip"
!define RUNTIME_ZIP_URL "https://ssd.mathworks.com/supportfiles/downloads/R2023a/Release/6/deployment_files/installer/complete/win64/MATLAB_Runtime_R2023a_Update_6_win64.zip"
!define TEMP_DIR "C:\temp\matlabRuntimeTmp"
!define TEMP_DIR_D "C:\\temp\\matlabRuntimeTmp"

Name "${APP_NAME}"
OutFile "${APP_NAME}_setup.exe"
InstallDir "C:\Program Files\${APP_NAME}"
RequestExecutionLevel admin

Section
InitPluginsDir
SetOutPath $PLUGINSDIR

; Download the GUI
inetc::get "${ZIP_URL}" "$PLUGINSDIR\LLSM_Processing_GUI.zip"
Pop $R0 ; Get the results
DetailPrint "Download result: $R0"

DetailPrint "Extracting the LLSM_Processing_GUI files..."
nsisunz::Unzip "$PLUGINSDIR\LLSM_Processing_GUI.zip" "$PLUGINSDIR"
Pop $0 ; Get the result of Unzip
StrCmp $0 "success" ok
  DetailPrint "$0" ;print error message to log
ok:

IfFileExists "C:\Program Files\MATLAB\MATLAB Runtime\R2023a\VersionInfo.xml" skip_runtime install_runtime 
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
DetailPrint "Installing LLSM_Processing_GUI files..."
CopyFiles /Silent "$PLUGINSDIR\LLSM_Processing_GUI" "$InstDir"

SectionEnd

Section "Install"
SetOutPath $INSTDIR
CreateShortcut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${APP_EXE}"
WriteUninstaller "$INSTDIR\uninstall_LLSM_Processing_GUI.exe"
SectionEnd

Section "Uninstall"
Delete "$DESKTOP\${APP_NAME}.lnk"
Delete "$INSTDIR\${APP_EXE}"
RMDir /r "$INSTDIR"
RMDir "$INSTDIR"
SectionEnd
