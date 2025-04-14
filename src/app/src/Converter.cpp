#include "Converter.hpp"

#include <algorithm>

#include <QJSEngine>

Converter::Converter(QObject* parent)
    : QObject(parent)
    , m_jsEngine(std::make_unique<QJSEngine>())
{
}
Converter::~Converter() {}

Q_INVOKABLE void Converter::processInput(QString const& value)
{
    if (value.isEmpty())
        return;

    QString func       = m_DataList[m_SelectedType].arg(value);
    QString finalValue = executeFunction(func);

    setConverted(finalValue);
}

QString const& Converter::getInputValue() const
{
    return m_InputValue;
}
void Converter::setInputValue(QString const& val)
{
    m_InputValue = val;
    emit inputValueChanged();
}

QString Converter::getConverted() const
{
    return m_LastInputed;
}
void Converter::setConverted(QString const& val)
{
    m_LastInputed = val;
    emit lastConvertedChanged();
}

QString Converter::executeFunction(QString const& func)
{
    QJSValue val = m_jsEngine->evaluate(func);
    return val.toString();
}

void Converter::setSecondType(QString const& second)
{
    m_SelectedType = second;

    processInput(m_LastInputed);
}
QString const& Converter::getSecondType() const
{
    return m_SelectedType;
}

QStringList Converter::getConverterList() const
{
    QStringList list;
    list.reserve(m_DataList.size());

    for (auto const& el : m_DataList)
        list.emplace_back(el.first);

    return list;
}
Q_INVOKABLE void Converter::setScheme(QVariantMap const& scheme)
{
    for (auto const [name, function] : scheme.toStdMap())
        m_DataList.emplace(name, function.toString());

    emit schemeLoaded();
}
