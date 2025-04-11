#pragma once

#include <QObject>

#include <QJsonDocument>

class ConverterHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentConverter MEMBER m_CurrentConverter READ GetActiveConverter WRITE SetActiveConverter);
    // Q_PROPERTY(QString  MEMBER  READ  WRITE )

public:
    ConverterHandler(QObject* parent = Q_NULLPTR);
    ~ConverterHandler() override;

    void           SetActiveConverter(QString const& type);
    QString const& GetActiveConverter() const;

    Q_INVOKABLE QVariantMap getScheme() const;

private:
    bool LoadConverterScheme();

signals:
    void convterterTypeChanged();

private:
    QJsonDocument m_ConverterScheme;
    QString       m_CurrentConverter;
};
