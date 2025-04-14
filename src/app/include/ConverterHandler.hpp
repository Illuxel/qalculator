#pragma once

#include <QObject>

#include <QJsonDocument>

class ConverterHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentConverter MEMBER m_CurrentConverter READ getActiveConverter WRITE setActiveConverter);

public:
    ConverterHandler(QObject* parent = Q_NULLPTR);
    ~ConverterHandler() override;

    void           setActiveConverter(QString const& type);
    QString const& getActiveConverter() const;

    Q_INVOKABLE QVariantMap getScheme() const;

private:
    bool loadConverterScheme();

signals:
    void convterterTypeChanged();

private:
    QJsonDocument m_ConverterScheme;
    QString       m_CurrentConverter;
};
