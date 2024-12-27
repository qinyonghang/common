#pragma once

#ifdef QNODEBUG

#define qTrace(fmt, ...)
#define qDebug(fmt, ...)
#define qInfo(fmt, ...)
#define qWarn(fmt, ...)
#define qError(fmt, ...)
#define qCritical(fmt, ...)

#else

#include <typeinfo>

#include "QObject.h"
#include "QSingletonProductor.h"
#include "spdlog/spdlog.h"

class QLog : public QObject {
public:
    template <typename... Args>
    using format_string_t = spdlog::format_string_t<Args...>;

    ~QLog() = default;

    void set_level(size_t level) {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
    }

    template <typename... Args>
    void trace(format_string_t<Args...> fmt, Args&&... args) {
        spdlog::trace(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void debug(format_string_t<Args...> fmt, Args&&... args) {
        spdlog::debug(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void info(format_string_t<Args...> fmt, Args&&... args) {
        spdlog::info(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warn(format_string_t<Args...> fmt, Args&&... args) {
        spdlog::warn(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void error(format_string_t<Args...> fmt, Args&&... args) {
        spdlog::error(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void critical(format_string_t<Args...> fmt, Args&&... args) {
        spdlog::critical(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void log(size_t level, format_string_t<Args...> fmt, Args&&... args) {
        spdlog::log(static_cast<spdlog::level::level_enum>(level), fmt,
                    std::forward<Args>(args)...);
    }

protected:
    QLog() : QObject(nullptr) { spdlog::set_level(spdlog::level::info); }

    friend class QSingletonProductor<QLog>;
};

#define qLogger() (QSingletonProductor<QLog>::get_instance())

#define qTrace(fmt, ...) qLogger().trace("[{}:{}]" fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define qDebug(fmt, ...) qLogger().debug("[{}:{}]" fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define qInfo(fmt, ...) qLogger().info("[{}:{}]" fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define qWarn(fmt, ...) qLogger().warn("[{}:{}]" fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define qError(fmt, ...) qLogger().error("[{}:{}]" fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define qCritical(fmt, ...) qLogger().critical("[{}:{}]" fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#endif

#define qCTrace(fmt, ...) qTrace("{}: " fmt, typeid(*this).name(), ##__VA_ARGS__)
#define qCDebug(fmt, ...) qDebug("{}: " fmt, typeid(*this).name(), ##__VA_ARGS__)
#define qCInfo(fmt, ...) qInfo("{}: " fmt, typeid(*this).name(), ##__VA_ARGS__)
#define qCWarn(fmt, ...) qWarn("{}: " fmt, typeid(*this).name(), ##__VA_ARGS__)
#define qCError(fmt, ...) qError("{}: " fmt, typeid(*this).name(), ##__VA_ARGS__)
#define qCCritical(fmt, ...) qCritical("{}: " fmt, typeid(*this).name(), ##__VA_ARGS__)

#define qMTrace(fmt, ...) qTrace("{}: " fmt, __func__, ##__VA_ARGS__)
#define qMDebug(fmt, ...) qDebug("{}: " fmt, __func__, ##__VA_ARGS__)
#define qMInfo(fmt, ...) qInfo("{}: " fmt, __func__, ##__VA_ARGS__)
#define qMWarn(fmt, ...) qWarn("{}: " fmt, __func__, ##__VA_ARGS__)
#define qMError(fmt, ...) qError("{}: " fmt, __func__, ##__VA_ARGS__)
#define qMCritical(fmt, ...) qCritical("{}: " fmt, __func__, ##__VA_ARGS__)

#define qCMTrace(fmt, ...) qTrace("{}::{}: " fmt, typeid(*this).name(), __func__, ##__VA_ARGS__)
#define qCMDebug(fmt, ...) qDebug("{}::{}: " fmt, typeid(*this).name(), __func__, ##__VA_ARGS__)
#define qCMInfo(fmt, ...) qInfo("{}::{}: " fmt, typeid(*this).name(), __func__, ##__VA_ARGS__)
#define qCMWarn(fmt, ...) qWarn("{}::{}: " fmt, typeid(*this).name(), __func__, ##__VA_ARGS__)
#define qCMError(fmt, ...) qError("{}::{}: " fmt, typeid(*this).name(), __func__, ##__VA_ARGS__)
#define qCMCCritical(fmt, ...)                                                                     \
    qCritical("{}::{}: " fmt, typeid(*this).name(), __func__, ##__VA_ARGS__)
