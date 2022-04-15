#pragma once

#include <string>

namespace relic
{
    static constexpr int k_info_messages_code = 0;
    static constexpr int k_warning_messages_code = 100;
    static constexpr int k_error_messages_code = 200;

    enum class LoggingType
    {
        info_ = k_info_messages_code,
        warning_ = k_warning_messages_code,
        error_bad_message_value = k_error_messages_code,
        error_number_out_of_bounds,

    };

    inline std::string toString(const LoggingType e)
    {
        switch (e)
        {
        case LoggingType::error_bad_message_value: return "Bad Message Value";
        case LoggingType::warning_: return "warning_";
        case LoggingType::error_number_out_of_bounds: return "Number out of Bounds";
        default: return "unknown";
        }
    }
}
