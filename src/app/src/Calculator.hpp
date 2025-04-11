#pragma once

#include "OperationHistory.hpp"

class QJSEngine;

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
    Q_ENUM(Command);

    enum WaitOperation
    {
        Cmd = 4,
        Function,
        Operator,
        Value
    };
    Q_ENUM(WaitOperation);

    Standart(QObject* parent = Q_NULLPTR);
    ~Standart() override;

    Q_INVOKABLE virtual void processButton(QString const& type, QString const& func, QString const& placeHolder);
    Q_INVOKABLE void         setHistory(History* history);

    Q_INVOKABLE void update();

    Q_INVOKABLE void getEqual();

    QString const& GetFinalValue() const;
    QString const& GetLastOperation() const;

private:
    void SetLastJoined(QString const& lastJoined);

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
    std::unique_ptr<QJSEngine> m_jsEngine;
    History*                   m_History = nullptr;

    QString m_BackEndExpression, m_FrontEndExpression;

    Command       m_LastCommand;
    WaitOperation m_LastOperation;
};

struct OperationElement : public HistoryElement
{
    QString FinalValue;
    QString UnsavedValue;
    QString LastJoined;
    QString BackEndExpression;

    Standart::WaitOperation LastOperation;

    QString placeHolderText() const override;
};
