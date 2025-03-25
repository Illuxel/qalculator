#pragma once

#include "OperationHistory.hpp"
#include <QJSEngine>
#include <QMetaEnum>
#include <QStringListModel>


class Standart : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString finalValue MEMBER m_FinalValue READ GetFinalValue NOTIFY finalValueChanged)
    QString m_FinalValue;

    Q_PROPERTY(QString enteredValue MEMBER m_UnsavedValue WRITE SetEnteredValue NOTIFY enteredValueChanged)
    QString m_UnsavedValue;

    Q_PROPERTY(QString lastOperation MEMBER m_LastJoined READ GetLastOperation NOTIFY lastOperationChanged)
    QString m_LastJoined;

public:
    enum Command
    {
        del = 0,
        clr,
        clrall,
        cnvrt,
        equal
    };
    Q_ENUM(Command)
    enum WaitOperation
    {
        Cmd = 4,
        Function,
        Operator,
        Value
    };
    Q_ENUM(WaitOperation)

public:
    Standart(QObject* parent = nullptr);
    ~Standart() override;

    Q_INVOKABLE virtual void processButton(QString const& type, QString const& func, QString const& placeHolder);
    Q_INVOKABLE void         setHistory(History* history);

    Q_INVOKABLE void update();

    Q_INVOKABLE void getEqual();

    QString const& GetFinalValue() const;
    QString const& GetLastOperation() const;

private:
    void ExecuteCommand(QString const& cmd);

    QString CalculateProduct();

    QString ConcatPHFunctionWithValue(QString const& placeHolder, double value) const;

    Q_INVOKABLE void SetEnteredValue(QString const& value);

    void AddEnteredValue(QChar const& value);
    void AddOperator(QChar const& op);
    void AddFunction(QString const& func, QString const& placeHolder);

    void DeleteEnteredValue();
    void ClearEntered();
    void ClearCalculations();

private slots:
    void onHistoryItemClicked(HistoryElement* item);

signals:
    void finalValueChanged();
    void enteredValueChanged();
    void lastOperationChanged();

private:
    QJSEngine* m_jsEngine = nullptr;
    History*   m_History  = nullptr;

    QString m_BackEndExpression, m_FrontEndExpression;

    Command       m_LastCommand;
    WaitOperation m_LastOperation;
};

class OperationElement : public HistoryElement
{
public:
    QString placeHolderText() const override;

    QString const& GetFinalValue() const;
    void           SetFinalValue(QString val);

    QString const& GetUnsavedValue() const;
    void           SetUnsavedValue(QString val);

    QString const& GetLastJoined() const;
    void           SetLastJoined(QString val);

    QString const& GetBackEndExpression() const;
    void           SetBackEndExpression(QString val);

    Standart::WaitOperation GetOperationType() const;
    void                    SetOperationType(Standart::WaitOperation val);

private:
    QString                 FinalValue, UnsavedValue, LastJoined, BackEndExpression;
    Standart::WaitOperation LastOperation;
};
