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
     
*step 5 may be unnecessary depending on your operating system, just ensure sample.h is present
  
The samplemc folder should include rc and mc but if you decide to use your computer's native mc and rc files they can typically be found in C:\Program Files (x86)\Windows Kits\10\bin\10.0..\x64\mc.exe) and C:\Program Files (x86)\Windows Kits\10\bin\10.0.18362.0\x64\rc.exe.

# Running WinSC
WinSC is designed to work from the command line and to take various arguments depending on the command.
Each command is run with the general command: winsc.exe [...arguments...]

# Query

Obtains and displays information about the specified service

**Syntax**: query [SERVICENAME]

# Create

Creates an entry for a service in the Service Control Manager database.

**Syntax**: create [SERVICENAME] [PATH]

# Describe

Display the description string for a specified service.

**Syntax**: describe [SERVICENAME]

# Config

Modifies the value of a service's entries in the registry and in the Service Control Manager database

**Syntax**: config [SERVICENAME] [PARAMETER] [VALUE]

Parameters: 
* start:          configure service start type
* error:          specify the severity of the error
* type:           specify service type

Values:
* start - takes values from the command line as text
* error - takes values from the command line as text
* type - takes values from the command line as text

# Start

Starts a service

**Syntax**: start [SERVICENAME]

# Stop

Sends a request to stop a service.

**Syntax**: stop [SERVICENAME]

# Failure

**Syntax**: failure [SERVICENAME] [PARAMETER] [VALUE]

Parameters:
* reset:          specifies the time after which to reset the failure count to zero if there are no failures
* reboot:         message to be broadcast to server users before rebooting
* command:        command-line command to be run when the specified service fails
* restart:        specifies the length of time to wait before restarting in milliseconds

Values:
* reset - takes value from the command line as an integer
* reboot - takes values from the command line as text enclosed in double quotation marks("  ")
* command - takes values from the command line as text enclosed in double quotation marks("  ")
* restart - takes value from the command line as an integer



