#pragma once

#include "pch.h"

namespace iw4
{
namespace mp_tu6
{
class stats : public Module
{
  public:
    stats();
    ~stats();

    const char *get_name() override
    {
        return "stats";
    }
};
} // namespace mp_tu6
} // namespace iw4
