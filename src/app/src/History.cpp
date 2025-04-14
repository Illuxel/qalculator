#include "History.hpp"

#include <QQmlApplicationEngine>

History::History(QObject* parent)
    : QObject(parent)
{
}
History::~History()
{
    for (auto& el : m_Elements)
        delete el;
}

void History::pushElement(HistoryElement* el)
{
    m_Elements.push_back(el);
    emit historyListChanged();
}
void History::popElement()
{
    HistoryElement* el = m_Elements.takeLast();
    delete el;
    emit historyListChanged();
}
void History::clearHistory()
{
    m_Elements.clear();
    emit historyListChanged();
}

QString History::placeHolderAt(int index)
{
    return m_Elements.at(index)->placeHolderText();
}

QString History::getCurrentItem()
{
    if (m_CurrentItem)
        m_CurrentItem->placeHolderText();
    return "";
}
void History::setCurrentItem(QString const& setEl)
{
    for (auto el : m_Elements)
        if (el->placeHolderText() == setEl)
            m_CurrentItem = el;

    emit currentItemChanged(m_CurrentItem);
}

QStringList History::getHistoryList() const
{
    QStringList m_HistoryList;
    for (auto el : m_Elements)
        m_HistoryList.push_back(el->placeHolderText());
    return m_HistoryList;
}
