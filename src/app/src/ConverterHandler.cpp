#include "ConverterHandler.hpp"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

ConverterHandler::ConverterHandler(QObject* parent)
    : QObject(parent)
{
    loadConverterScheme();
}
ConverterHandler::~ConverterHandler() {}

bool ConverterHandler::loadConverterScheme()
{
    QFile file("ConverterData.json");
    if (!file.open(QFile::ReadOnly))
        return false;

    m_ConverterScheme  = QJsonDocument::fromJson(file.readAll());
    m_CurrentConverter = "Angle";

    return !m_ConverterScheme.isNull();
}

void ConverterHandler::setActiveConverter(QString const& converter)
{
    m_CurrentConverter = converter;
}

QString const& ConverterHandler::getActiveConverter() const
{
    return m_CurrentConverter;
}

Q_INVOKABLE QVariantMap ConverterHandler::getScheme() const
{
    return m_ConverterScheme.object()[m_CurrentConverter].toObject().toVariantMap();
}
