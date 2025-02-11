#include <iostream>
#include <vector>
#include <Windows.h>

const BYTE ALPHA_HIDE = 0;
const BYTE ALPHA_SHOW = 255;

std::vector<HWND> global_windows;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    const std::wstring& targetClass = *reinterpret_cast<std::wstring*>(lParam);

    wchar_t className[256];
    if (GetClassName(hwnd, className, 256) > 0) {
        if (targetClass == className) {
            global_windows.push_back(hwnd);
        }
    }

    return TRUE;
}

std::vector<HWND> FindWindowsByClass(const std::wstring& class_name) {
    global_windows.clear();
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&class_name));
    return global_windows;
}

void SetWindowAlpha(HWND window_handle, BYTE alpha) {
    SetWindowLong(window_handle, GWL_EXSTYLE, GetWindowLong(window_handle, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(window_handle, 0, alpha, LWA_ALPHA);

    RedrawWindow(window_handle, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
}

std::vector<HWND> GetAllTaskbarWindows() {
    auto primary_windows = FindWindowsByClass(L"Shell_TrayWnd");
    auto secondary_windows = FindWindowsByClass(L"Shell_SecondaryTrayWnd");

    primary_windows.insert(primary_windows.end(), secondary_windows.begin(), secondary_windows.end());

    return primary_windows;
}

void SetTaskbarsHidden(bool hidden) {
    auto window_handles = GetAllTaskbarWindows();
    
    for (auto handle : window_handles) {
        std::cout << handle << std::endl;
        SetWindowAlpha(handle, hidden ? ALPHA_HIDE : ALPHA_SHOW);
    }
}

void MainLoop() {
    while (true) {
        Sleep(1000);
        SetTaskbarsHidden(true);
    }
}

#ifdef NDEBUG
int WinMain(HINSTANCE _instance_handle, HINSTANCE _prev_instance_handle, LPSTR cmd_line, int _show_cmd) {
    if (cmd_line == "--hide") {
        SetTaskbarsHidden(true);
        return 0;
    }

    if (cmd_line == "--show") {
        SetTaskbarsHidden(false);
        return 0;
    }

    MainLoop();
    return 0;
}
#else
int main(int argc, char* argv[])
{
    if (argv[1] == "--hide") {
        SetTaskbarsHidden(true);
        return 0;
    }

    if (argv[1] == "--show") {
        SetTaskbarsHidden(false);
        return 0;
    }

    MainLoop();
}
#endif
