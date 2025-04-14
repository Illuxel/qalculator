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
    Q_PROPERTY(QStringList list READ getHistoryList NOTIFY historyListChanged);
    Q_PROPERTY(QString currentItem READ getCurrentItem WRITE setCurrentItem NOTIFY currentItemChanged);

public:
    History(QObject* parent = Q_NULLPTR);
    ~History() override;

    Q_INVOKABLE QString placeHolderAt(int index);
    Q_INVOKABLE void    clearHistory();

    QStringList getHistoryList() const;
    QString     getCurrentItem();

    void setCurrentItem(QString const& el);

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
