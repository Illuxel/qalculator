#pragma once

#include <QMetaEnum>
#include <QObject>

template <typename Enum>
inline Enum ConvertStringToEnum(QString const& enStr)
{
    QMetaEnum en = QMetaEnum::fromType<Enum>();
    if (enStr.isEmpty())
        return static_cast<Enum>(-1);
    return static_cast<Enum>(en.keyToValue(enStr.toUtf8()));
}
