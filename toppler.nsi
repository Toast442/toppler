!define NAME "Tower Toppler"
!define PACKAGE "toppler"
!define VERSION "1.1.3"
!define URL "http://toppler.sourceforge.net/"
!define FLATDIR "toppler-1.1.3-win32"
!define OUTFILE "${FLATDIR}.exe"
!define MAINPROG "${PACKAGE}.exe"
!define MAINICON "${PACKAGE}.ico"
!define SMDIR "$SMPROGRAMS\${NAME}"
!define UNINSTPROG "uninstall.exe"
!define LICENSE "COPYING.txt"

Name "${NAME}"
OutFile "${OUTFILE}"
InstallDir "$PROGRAMFILES\${PACKAGE}"
InstallDirRegKey HKLM "Software\${PACKAGE}" "Install_Dir"
SetCompressor LZMA
XPStyle off

Page license
Page components
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

LicenseData "${FLATDIR}\${LICENSE}"

InstType "Full"

Section "-Install Uninstaller"
  SetOutPath "$INSTDIR"

  WriteUninstaller "$INSTDIR\${UNINSTPROG}"
  WriteRegStr HKLM \
              "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PACKAGE}" \
              "DisplayName" "${NAME}"
  WriteRegStr HKLM \
              "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PACKAGE}" \
              "UninstallString" '"$INSTDIR\${UNINSTPROG}"'
SectionEnd

Section "!${NAME} - ${VERSION}"
  SectionIn 1
  SetOutPath "$INSTDIR"

  File "${FLATDIR}\*.exe"
  File "${FLATDIR}\*.ico"
  File "${FLATDIR}\*.ttm"
  File "${FLATDIR}\*.dat"
  File "${FLATDIR}\*.ogg"
  File "${FLATDIR}\*.hsc"
  File "${FLATDIR}\*.txt"

  SetOutPath "$INSTDIR\locale\cz\LC_MESSAGES"
  File     "${FLATDIR}\locale\cz\LC_MESSAGES\${PACKAGE}.mo"
  SetOutPath "$INSTDIR\locale\de\LC_MESSAGES"
  File     "${FLATDIR}\locale\de\LC_MESSAGES\${PACKAGE}.mo"
  SetOutPath "$INSTDIR\locale\eu\LC_MESSAGES"
  File     "${FLATDIR}\locale\eu\LC_MESSAGES\${PACKAGE}.mo"
  SetOutPath "$INSTDIR\locale\fi\LC_MESSAGES"
  File     "${FLATDIR}\locale\fi\LC_MESSAGES\${PACKAGE}.mo"
  SetOutPath "$INSTDIR\locale\fr\LC_MESSAGES"
  File     "${FLATDIR}\locale\fr\LC_MESSAGES\${PACKAGE}.mo"
  SetOutPath "$INSTDIR\locale\pt\LC_MESSAGES"
  File     "${FLATDIR}\locale\pt\LC_MESSAGES\${PACKAGE}.mo"
  SetOutPath "$INSTDIR\locale\sv\LC_MESSAGES"
  File     "${FLATDIR}\locale\sv\LC_MESSAGES\${PACKAGE}.mo"
  SetOutPath "$INSTDIR\locale\ro\LC_MESSAGES"
  File     "${FLATDIR}\locale\ro\LC_MESSAGES\${PACKAGE}.mo"
SectionEnd

Section "Start Menu Entry"
  SectionIn 1
  SetOutPath "$INSTDIR"

  CreateDirectory "${SMDIR}"
  CreateShortCut "${SMDIR}\${NAME}.lnk" "$INSTDIR\${MAINPROG}" "" "$INSTDIR\${MAINICON}"
  WriteINIStr "${SMDIR}\Homepage.url" "InternetShortcut" "URL" "${URL}"
  CreateShortCut "${SMDIR}\Read Me.lnk" "$INSTDIR\README.txt"
  CreateShortCut "${SMDIR}\Uninstall.lnk" "$INSTDIR\${UNINSTPROG}"
SectionEnd

Section "Desktop Entry"
  SectionIn 1
  SetOutPath "$INSTDIR"

  CreateShortCut "$DESKTOP\${NAME}.lnk" "$INSTDIR\${MAINPROG}" "" "$INSTDIR\${MAINICON}"
SectionEnd

UninstallText "This will uninstall ${NAME} from your system:"

Section "Uninstall"
  Delete   "$DESKTOP\${NAME}.lnk"

  Delete   "${SMDIR}\${NAME}.lnk"
  Delete   "${SMDIR}\Homepage.url"
  Delete   "${SMDIR}\Read Me.lnk"
  Delete   "${SMDIR}\Uninstall.lnk"
  RMDir    "${SMDIR}"

  Delete   $INSTDIR\*.exe
  Delete   $INSTDIR\*.ico
  Delete   $INSTDIR\*.ttm
  Delete   $INSTDIR\*.dat
  Delete   $INSTDIR\*.ogg
  Delete   $INSTDIR\*.hsc
  Delete   $INSTDIR\*.txt
  Delete   $INSTDIR\.${PACKAGE}.rc
  RMDir /r $INSTDIR\locale
  Delete   $INSTDIR\${UNINSTPROG}
  RMDir    $INSTDIR

  DeleteRegKey HKLM \
               "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PACKAGE}"
SectionEnd

Function .onInstSuccess
  SetOutPath "$INSTDIR"

  ExecShell open "$INSTDIR\README.txt"
FunctionEnd
