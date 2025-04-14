#pragma once

#include <QObject>

class QJSEngine;

class History;
class HistoryElement;

class Standart : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString finalValue MEMBER m_FinalValue READ getFinalValue NOTIFY finalValueChanged)
    Q_PROPERTY(QString enteredValue MEMBER m_UnsavedValue WRITE setEnteredValue NOTIFY enteredValueChanged)
    Q_PROPERTY(QString lastOperation MEMBER m_LastJoined READ getLastOperation NOTIFY lastOperationChanged)

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

    Standart(QObject* parent = Q_NULLPTR);
    ~Standart() override;

    Q_INVOKABLE virtual void processButton(QString const& type, QString const& func, QString const& placeHolder);
    Q_INVOKABLE void         setHistory(History* history);

    Q_INVOKABLE void update();

    Q_INVOKABLE void getEqual();

    QString const& getFinalValue() const;
    QString const& getLastOperation() const;

private:
    void setLastJoined(QString const& lastJoined);

    void executeCommand(QString const& cmd);

    QString calculateProduct();

    QString concatPHFunctionWithValue(QString const& placeHolder, double value) const;

    Q_INVOKABLE void setEnteredValue(QString const& value);

    void addEnteredValue(QChar const& value);
    void addOperator(QChar const& op);
    void addFunction(QString const& func, QString const& placeHolder);

    void deleteEnteredValue();
    void clearEntered();
    void clearCalculations();

private slots:
    void onHistoryItemClicked(HistoryElement* item);

signals:
    void finalValueChanged();
    void enteredValueChanged();
    void lastOperationChanged();

private:
    std::unique_ptr<QJSEngine> m_jsEngine;
    History*                   m_History = nullptr;

    QString m_FinalValue;
    QString m_UnsavedValue;
    QString m_LastJoined;

    QString m_BackEndExpression, m_FrontEndExpression;

    Command       m_LastCommand;
    WaitOperation m_LastOperation;
};
