#include "pch.h"
#include "components/scr_parser.h"

namespace
{
uint32_t ShowKeyboard(const wchar_t *title, const wchar_t *description, const wchar_t *defaultText, std::string &result,
                      size_t maxLength, uint32_t keyboardType)
{
    size_t realMaxLength = maxLength + 1;
    XOVERLAPPED overlapped = {};

    std::vector<wchar_t> wideBuffer(realMaxLength);
    std::vector<char> buffer(realMaxLength);

    XShowKeyboardUI(0, keyboardType, defaultText, title, description, wideBuffer.data(), realMaxLength, &overlapped);

    while (!XHasOverlappedIoCompleted(&overlapped))
        Sleep(100);

    if (XGetOverlappedResult(&overlapped, nullptr, TRUE) == ERROR_SUCCESS)
    {
        wcstombs_s(nullptr, buffer.data(), realMaxLength, wideBuffer.data(), realMaxLength * sizeof(wchar_t));
        result = buffer.data();
        return ERROR_SUCCESS;
    }

    return ERROR_CANCELLED;
}
} // namespace

namespace iw3
{
namespace sp
{

Detour CL_GamepadButtonEvent_Detour;

void CL_GamepadButtonEvent_Hook(int localClientNum, int controllerIndex, int key, int down, unsigned int time)
{
    CL_GamepadButtonEvent_Detour.GetOriginal<decltype(CL_GamepadButtonEvent)>()(localClientNum, controllerIndex, key,
                                                                                down, time);

    static bool commandKeyboardButtonDown = false;

    if (key == K_DPAD_DOWN)
    {
        if (!down)
        {
            commandKeyboardButtonDown = false;
        }
        else if (!commandKeyboardButtonDown)
        {
            commandKeyboardButtonDown = true;

            std::string value;
            auto result = ShowKeyboard(L"Enter command", L"", L"", value, 100, 0);
            if (result == ERROR_SUCCESS)
            {
                Cbuf_AddText(0, value.c_str());
            }
        }
    }
}

static cmd_function_s Cmd_Dumpraw_f_VAR;

void Cmd_Dumpraw_f()
{
    XAssetHeader files[2048];
    auto count = DB_GetAllXAssetOfType_FastFile(ASSET_TYPE_RAWFILE, files, 2048);

    for (int i = 0; i < count; i++)
    {
        auto rawfile = files[i].rawfile;
        std::string asset_name = rawfile->name;
        std::replace(asset_name.begin(), asset_name.end(), '/', '\\'); // Replace forward slashes with backslashes
        filesystem::write_file_to_disk((std::string(DUMP_DIR) + "\\" + asset_name).c_str(), rawfile->buffer,
                                       rawfile->len);
    }
}

IW3_SP_Plugin::IW3_SP_Plugin()
{
    DbgPrint("IW3 SP: Plugin loaded\n");
    RegisterModule(new Config());
    RegisterModule(new scr_parser());

    CL_GamepadButtonEvent_Detour = Detour(CL_GamepadButtonEvent, CL_GamepadButtonEvent_Hook);
    CL_GamepadButtonEvent_Detour.Install();

    Cmd_AddCommandInternal("dumpraw", Cmd_Dumpraw_f, &Cmd_Dumpraw_f_VAR);
}

IW3_SP_Plugin::~IW3_SP_Plugin()
{
    CL_GamepadButtonEvent_Detour.Remove();
}

} // namespace sp
} // namespace iw3
