#pragma once

#include "ConverterHandler.hpp"
#include <QHash>
#include <QStringListModel>

class Converter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList typeList READ GetConverterList NOTIFY schemeLoaded)
    Q_PROPERTY(QString secondType READ GetSecondType WRITE SetSecondType)
    Q_PROPERTY(QString inputValue READ GetInputValue WRITE SetInputValue NOTIFY inputValueChanged)

    Q_PROPERTY(QString convertedValue READ GetConverted NOTIFY lastConvertedChanged)

public:
    enum ButtonType
    {
        Value = 2,
        Function
    };
    Q_ENUM(ButtonType)

    Converter(QObject* parent = nullptr);

    Q_INVOKABLE void processInput(QString const& value);

    QString const& GetInputValue() const;
    void           SetInputValue(QString const& val);

    QString GetConverted() const;
    void    SetConverted(QString const& val);

    void           SetSecondType(QString const& second);
    QString const& GetSecondType() const;

    QStringList      GetConverterList() const;
    Q_INVOKABLE void setScheme(QVariantMap const& scheme);

    ~Converter() override;

private:
    QString ExecuteFunction(QString const& func);

signals:
    void schemeLoaded();

    void inputValueChanged();
    void lastConvertedChanged();

private:
    QJSEngine* m_jsEngine = nullptr;
    // first - data name
    // second - data function
    QMap<QString, QString> m_DataList;

    QString m_InputValue;

    QString m_SelectedType;
    QString m_LastInputed;
};
