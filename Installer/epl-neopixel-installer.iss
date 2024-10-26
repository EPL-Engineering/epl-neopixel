; -- epl-neopixel-installer.iss --
;
; Note the use of relative paths: deviating from the recommended file hierarchy 
; will break this install configuration.


; Set the following three variables
#define exeName "NeopixelController.exe" ; i.e.: the "Target filename" set in the LabVIEW project explorer
#define appName "Neopixel Controller"    ; this is arbitrary. It controls the install folder location and the desktop shortcut name
#define iconName "Neopixel Ring Lit.ico"

; In normal use, should not need to edit below here

; Extracts the semantic version from the executable. Only retains the patch number if it is greater than zero.
#define SemanticVersion() \
   GetVersionComponents("..\Build\" + exeName, Local[0], Local[1], Local[2], Local[3]), \
   Str(Local[0]) + "." + Str(Local[1]) + ((Local[2]>0) ? "." + Str(Local[2]) : "")
    
; The installer contains the semantic version number, but replaces the dots with dashes so it doesn't look like a file extension.
#define installerName StringChange(appName, ' ', '_') + "_" + StringChange(SemanticVersion(), '.', '-')


[Setup]
AppName={#appName}
AppVerName={#appName} V{#SemanticVersion()}
DefaultDirName={commonpf}\EPL\{#appName}\V{#SemanticVersion()}
OutputDir=Output
DefaultGroupName=EPL
AllowNoIcons=yes
OutputBaseFilename={#installerName}
UsePreviousAppDir=no
UsePreviousGroup=no
UsePreviousSetupType=no
DisableProgramGroupPage=yes
PrivilegesRequired=admin

[Dirs]
; Make sure the "C:\ProgramData\EPL" folder exists. Settings files are typically written here.
Name: "{commonappdata}\EPL";

[Files]
Source: "..\Build\*.*"; DestDir: "{app}"; Flags: replacesameversion;
Source: "..\Images\*.ico"; DestDir: "{app}"; Flags: replacesameversion;
Source: "..\Arduino\*.ino"; DestDir: "{userdocs}\Arduino\neopixel-controller"; Flags: replacesameversion;

[Icons]
Name: "{commondesktop}\{#appName}"; Filename: "{app}\{#exeName}"; IconFilename: "{app}\{#iconName}"; IconIndex: 0;



