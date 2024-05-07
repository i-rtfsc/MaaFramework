#pragma once

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#define MAA_FILE MAA_LOG_NS::pertty_file(__FILE__)
#define MAA_LINE std::string_view("L" LINE_STRING)
#ifdef _MSC_VER
#define MAA_FUNCTION std::string_view(__FUNCTION__)
#else
#define MAA_FUNCTION std::string_view(__PRETTY_FUNCTION__)
#endif
#define LOG_ARGS MAA_FILE, MAA_LINE, MAA_FUNCTION

#define LogFatal MAA_LOG_NS::Logger::get_instance().fatal(LOG_ARGS)
#define LogError MAA_LOG_NS::Logger::get_instance().error(LOG_ARGS)
#define LogWarn MAA_LOG_NS::Logger::get_instance().warn(LOG_ARGS)
#define LogInfo MAA_LOG_NS::Logger::get_instance().info(LOG_ARGS)
#define LogDebug MAA_LOG_NS::Logger::get_instance().debug(LOG_ARGS)
#define LogTrace MAA_LOG_NS::Logger::get_instance().trace(LOG_ARGS)

#define LogFunc                                                   \
    MAA_LOG_NS::LogScopeLeaveHelper ScopeHelperVarName(LOG_ARGS); \
    MAA_LOG_NS::LogScopeEnterHelper(LOG_ARGS)()

#define VAR_RAW(x) "[" << #x << "=" << (x) << "] "
#define VAR(x) MAA_LOG_NS::separator::none << VAR_RAW(x) << MAA_LOG_NS::separator::space
#define VAR_VOIDP_RAW(x) "[" << #x << "=" << reinterpret_cast<void*>(x) << "] "
#define VAR_VOIDP(x) MAA_LOG_NS::separator::none << VAR_VOIDP_RAW(x) << MAA_LOG_NS::separator::space
