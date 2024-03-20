# WinSC
A tool that emulates Windows sc.exe capabilities

# Before running WinSC
Before you run this program a sample.mc must be built. This is a resource-only DLL that the program will rely on.
To build the DLL do the following: 
  1. Open command prompt as administrator and run the following commands
  2. cd [path to samplemc]
  3. mc -U sample.mc
  4. rc -r sample.rc
  5. link -dll -noentry -out:sample.dll sample.res
     
* step 5 may be unnecessary depending on your operating system

The samplemc folder should include rc and mc but if you decide to use your computer's native mc and rc files they can typically be found in C:\Program Files (x86)\Windows Kits\10\bin\10.0..\x64\mc.exe) and C:\Program Files (x86)\Windows Kits\10\bin\10.0.18362.0\x64\rc.exe.

# Running WinSC
WinSC is designed to work from the command line and to take various arguments depending on the command.
