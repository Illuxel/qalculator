#pragma once

#include <QObject>

class QJSEngine;

class Converter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString secondType READ GetSecondType WRITE SetSecondType);
    Q_PROPERTY(QString inputValue READ GetInputValue WRITE SetInputValue NOTIFY inputValueChanged);
    Q_PROPERTY(QString convertedValue READ GetConverted NOTIFY lastConvertedChanged);

    Q_PROPERTY(QStringList typeList READ GetConverterList NOTIFY schemeLoaded);

public:
    enum ButtonType
    {
        Value = 2,
        Function
    };
    Q_ENUM(ButtonType);

    Converter(QObject* parent = Q_NULLPTR);
    ~Converter() override;

    Q_INVOKABLE void processInput(QString const& value);

    QString const& GetInputValue() const;
    void           SetInputValue(QString const& val);

    QString GetConverted() const;
    void    SetConverted(QString const& val);

    void           SetSecondType(QString const& second);
    QString const& GetSecondType() const;

    QStringList      GetConverterList() const;
    Q_INVOKABLE void setScheme(QVariantMap const& scheme);

private:
    QString ExecuteFunction(QString const& func);

signals:
    void schemeLoaded();

    void inputValueChanged();
    void lastConvertedChanged();

private:
    std::unique_ptr<QJSEngine> m_jsEngine;

    QString m_InputValue;
    QString m_SelectedType;
    QString m_LastInputed;

    // first - data name
    // second - data function
    std::map<QString, QString> m_DataList;
};
