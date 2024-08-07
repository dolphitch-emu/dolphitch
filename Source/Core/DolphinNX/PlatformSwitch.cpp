// Copyright 2018 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <cstdio>
#include <thread>

#include "Core/Core.h"
#include "Core/System.h"
#include "DolphinNoGUI/Platform.h"

namespace
{
class PlatformSwitch : public Platform
{
public:
  void SetTitle(const std::string& title) override;
  void MainLoop() override;

  WindowSystemInfo GetWindowSystemInfo() const override;
};

void PlatformSwitch::SetTitle(const std::string& title)
{
  //std::fprintf(stdout, "%s\n", title.c_str());
}

void PlatformSwitch::MainLoop()
{
  while (m_running.IsSet())
  {
    UpdateRunningFlag();
    Core::HostDispatchJobs(Core::System::GetInstance());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

WindowSystemInfo PlatformSwitch::GetWindowSystemInfo() const
{
  WindowSystemInfo wsi;
  wsi.type = WindowSystemType::Headless;
  wsi.display_connection = nullptr;
  wsi.render_window = nullptr;
  wsi.render_surface = nullptr;
  return wsi;
}

}  // namespace

std::unique_ptr<Platform> Platform::CreateSwitchPlatform()
{
  return std::make_unique<PlatformSwitch>();
}
