#pragma once

#include "config.h"
#include "version.h"
namespace branding
{
inline const char *GetBrandingString()
{
    static char brandingBuffer[256];

    if (Config::active_mod.empty())
    {
        _snprintf_s(brandingBuffer, sizeof(brandingBuffer), "CoD ^2Xe^7 r%d", BUILD_NUMBER);
    }
    else
    {
        _snprintf_s(brandingBuffer, sizeof(brandingBuffer), "CoD ^2Xe^7 r%d\nMod: %s", BUILD_NUMBER,
                    Config::active_mod.c_str());
    }

    return brandingBuffer;
}
} // namespace branding
