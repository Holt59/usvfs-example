#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
#include <memory>

#include "usvfs.h"

int main()
{
  auto parameters = usvfsCreateParameters();

  usvfsSetInstanceName(parameters, "instance");
  usvfsSetDebugMode(parameters, false);
  usvfsSetLogLevel(parameters, LogLevel::Debug);
  usvfsSetCrashDumpType(parameters, CrashDumpsType::None);
  usvfsSetCrashDumpPath(parameters, "");

  usvfsInitLogging(false);
  usvfsCreateVFS(parameters);

  // map stuff
  usvfsVirtualLinkDirectoryStatic(L"./lib", L"C:/", LINKFLAG_RECURSIVE);

  // spawn process
  {
    STARTUPINFOW si{0};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{0};
    WCHAR command[] = L"cmd.exe /C dir C:\\";

    if (usvfsCreateProcessHooked(nullptr, command, nullptr, nullptr, FALSE, 0, nullptr,
                                 nullptr, &si, &pi)) {
      WaitForSingleObject(pi.hProcess, INFINITE);

      DWORD exit = 99;
      if (!GetExitCodeProcess(pi.hProcess, &exit)) {
        std::cerr << "process failed\n";
      }

      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);
    } else {
      std::cerr << "create process failed\n";
    }
  }

  // free stuff
  usvfsDisconnectVFS();
  usvfsFreeParameters(parameters);
}
