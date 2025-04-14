#pragma once

#include <QObject>
#include <QtQmlIntegration>

class QJSEngine;

class Converter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString secondType READ getSecondType WRITE setSecondType);
    Q_PROPERTY(QString inputValue READ getInputValue WRITE setInputValue NOTIFY inputValueChanged);
    Q_PROPERTY(QString convertedValue READ getConverted NOTIFY lastConvertedChanged);
    Q_PROPERTY(QStringList typeList READ getConverterList NOTIFY schemeLoaded);

public:
    enum ButtonType
    {
        Value = 2,
        Function
    };
    Q_ENUM(ButtonType)

    Converter(QObject* parent = Q_NULLPTR);
    ~Converter() override;

    Q_INVOKABLE void processInput(QString const& value);

    QString const& getInputValue() const;
    void           setInputValue(QString const& val);

    QString getConverted() const;
    void    setConverted(QString const& val);

    void           setSecondType(QString const& second);
    QString const& getSecondType() const;

    QStringList      getConverterList() const;
    Q_INVOKABLE void setScheme(QVariantMap const& scheme);

private:
    QString executeFunction(QString const& func);

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
