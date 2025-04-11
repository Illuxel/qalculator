#pragma once

#include <QObject>

class HistoryElement
{
    Q_GADGET

public:
    virtual ~HistoryElement() = default;

    virtual QString placeHolderText() const = 0;
};

class History : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList list READ GetHistoryList NOTIFY historyListChanged);
    Q_PROPERTY(QString currentItem READ GetCurrentItem WRITE SetCurrentItem NOTIFY currentItemChanged);
    Q_PROPERTY(History* object READ GetObject);

public:
    History(QObject* parent = Q_NULLPTR);
    ~History() override;

    Q_INVOKABLE QString placeHolderAt(int index);
    Q_INVOKABLE void    clearHistory();

    History* GetObject();

    QStringList GetHistoryList() const;
    QString     GetCurrentItem();

    void SetCurrentItem(QString const& el);

public slots:
    Q_INVOKABLE void pushElement(HistoryElement* el);
    Q_INVOKABLE void popElement();

signals:
    void historyListChanged();
    void currentItemChanged(HistoryElement* item);

private:
    QList<HistoryElement*> m_Elements;
    HistoryElement*        m_CurrentItem;
};
