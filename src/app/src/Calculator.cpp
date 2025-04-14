#include "Calculator.hpp"

#include "History.hpp"
#include "Utils.hpp"

#include <QJSEngine>

struct OperationElement : public HistoryElement
{
    QString FinalValue;
    QString UnsavedValue;
    QString LastJoined;
    QString BackEndExpression;

    Standart::WaitOperation LastOperation;

    QString placeHolderText() const override;
};

Standart::Standart(QObject* parent)
    : QObject{ parent }
    , m_jsEngine(std::make_unique<QJSEngine>())
{
    m_UnsavedValue  = '0';
    m_LastOperation = Value;
}
Standart::~Standart() {}

void Standart::processButton(QString const& type, QString const& func, QString const& placeHolder)
{
    QString capitalized = type;
    capitalized[0]      = type[0].toUpper();
    WaitOperation t     = ConvertStringToEnum<WaitOperation>(capitalized);

    switch (t)
    {
        case Standart::Cmd:      executeCommand(func); break;
        case Standart::Function: addFunction(func, placeHolder); break;
        case Standart::Operator: addOperator(*func.begin()); break;
        case Standart::Value:    addEnteredValue(*func.begin()); break;
    }
}
void Standart::setHistory(History* history)
{
    connect(history, &History::currentItemChanged, this, &Standart::onHistoryItemClicked);
    m_History = history;
}

void Standart::update()
{
    emit lastOperationChanged();
    emit enteredValueChanged();
}

void Standart::getEqual()
{
    if (m_BackEndExpression.isEmpty())
        return;

    if (m_LastOperation == Function)
    {
        m_UnsavedValue = m_FinalValue;
        m_BackEndExpression.clear();
    }

    if (m_LastOperation == Cmd)
    {
        if (m_LastCommand == equal)
        {
            m_UnsavedValue = m_FinalValue;
            m_LastJoined   = m_FinalValue;
            m_BackEndExpression.clear();
        }
    }

    if (!m_BackEndExpression.end()->isNumber())
        m_BackEndExpression += m_UnsavedValue;

    m_FinalValue = calculateProduct();
    emit finalValueChanged();

    m_LastJoined = m_BackEndExpression;

    OperationElement* el  = new OperationElement();
    el->FinalValue        = m_FinalValue;
    el->UnsavedValue      = m_UnsavedValue;
    el->LastJoined        = m_LastJoined;
    el->BackEndExpression = m_BackEndExpression;
    el->LastOperation     = m_LastOperation;

    m_History->pushElement(el);

    m_UnsavedValue.clear();
    emit lastOperationChanged();
}

void Standart::executeCommand(QString const& cmd)
{
    Command const c = ConvertStringToEnum<Command>(cmd);

    switch (c)
    {
        case Standart::del:    deleteEnteredValue(); break;
        case Standart::clr:    clearEntered(); break;
        case Standart::clrall: clearCalculations(); break;
        case Standart::equal:  getEqual(); break;
        case Standart::cnvrt:
            if (m_UnsavedValue[0] == '0')
                return;

            if (m_UnsavedValue.isEmpty())
            {
                if (m_FinalValue.indexOf('-') != -1)
                    m_FinalValue.remove(0, 1);
                else
                    m_FinalValue.push_front('-');

                m_UnsavedValue = m_FinalValue;

                emit finalValueChanged();
            }
            else
            {
                if (m_UnsavedValue.indexOf('-') != -1)
                    m_UnsavedValue.remove(0, 1);
                else
                    m_UnsavedValue.push_front('-');

                m_FinalValue = m_UnsavedValue;

                emit enteredValueChanged();
            }

            break;
    }

    m_LastCommand   = c;
    m_LastOperation = Cmd;
}

Q_INVOKABLE void Standart::setEnteredValue(QString const& value)
{
    m_UnsavedValue  = value;
    m_LastOperation = Value;

    emit enteredValueChanged();
}
void Standart::addEnteredValue(QChar const& value)
{
    if (!m_UnsavedValue.isEmpty())
    {
        if (m_UnsavedValue.left(2) != "0." && value.isSymbol())
        {
            return;
        }
        if (m_UnsavedValue[0] == '0' && m_UnsavedValue.size() == 1 && value.isNumber())
            m_UnsavedValue.clear();
    }
    else
    {
        if (value == '.')
            return;
    }

    if (m_LastOperation == Cmd)
        if (m_LastCommand == equal)
            m_UnsavedValue = value;

    if (m_LastOperation == Operator)
    {
        m_UnsavedValue = value;
    }
    else
    {
        m_UnsavedValue += value;
    }

    m_LastOperation = Value;
    emit enteredValueChanged();
}

void Standart::addOperator(QChar const& op)
{
    if (m_LastOperation == Cmd)
    {
        if (m_LastCommand == equal)
        {
            m_UnsavedValue = m_FinalValue;
            m_BackEndExpression.clear();
        }
    }

    if (m_LastOperation == Operator)
    {
        m_BackEndExpression.replace(m_BackEndExpression.last(1), op);
    }
    else if (m_LastOperation == Function)
    {
        m_UnsavedValue      = m_FinalValue;
        m_BackEndExpression = m_FinalValue + op;
    }
    else
    {
        m_BackEndExpression += m_UnsavedValue;
        m_BackEndExpression += op;
    }

    m_LastJoined = m_BackEndExpression;

    emit lastOperationChanged();

    m_LastOperation = Operator;
}
void Standart::addFunction(QString const& func, QString const& placeHolder)  // Math.pow(%1, 2)
{
    if (m_LastOperation == Function)
    {
        m_BackEndExpression = func.arg(m_FinalValue);
        m_LastJoined        = concatPHFunctionWithValue(placeHolder, m_FinalValue.toDouble());
        m_FinalValue        = calculateProduct();
        m_UnsavedValue      = m_FinalValue;

        m_LastOperation = Function;

        OperationElement* el  = new OperationElement();
        el->FinalValue        = m_FinalValue;
        el->UnsavedValue      = m_UnsavedValue;
        el->LastJoined        = m_LastJoined;
        el->BackEndExpression = m_BackEndExpression;
        el->LastOperation     = m_LastOperation;

        m_History->pushElement(el);

        emit lastOperationChanged();
        emit finalValueChanged();

        return;
    }
    else
    {
        if (m_LastOperation != Value && m_LastOperation != Cmd)
        {
            if (m_LastCommand != equal)
                return;
            return;
        }
    }

    if (m_LastOperation == Cmd)
    {
        if (m_LastCommand == equal)
        {
            m_UnsavedValue = m_FinalValue;
        }
    }

    m_BackEndExpression = func.arg(m_UnsavedValue);
    m_FinalValue        = calculateProduct();

    m_LastJoined    = concatPHFunctionWithValue(placeHolder, m_UnsavedValue.toDouble());
    m_LastOperation = Function;

    OperationElement* el  = new OperationElement();
    el->FinalValue        = m_FinalValue;
    el->UnsavedValue      = m_UnsavedValue;
    el->LastJoined        = m_LastJoined;
    el->BackEndExpression = m_BackEndExpression;
    el->LastOperation     = m_LastOperation;

    m_History->pushElement(el);

    emit lastOperationChanged();
    emit finalValueChanged();
}

void Standart::deleteEnteredValue()
{
    if (m_UnsavedValue.isEmpty())
    {
        m_UnsavedValue = '0';
        return;
    }

    if (m_UnsavedValue.size() == 2 && m_UnsavedValue[0] == '-')
        m_UnsavedValue = '0';
    else
        m_UnsavedValue.remove(m_UnsavedValue.size() - 1, 1);

    emit enteredValueChanged();
}

void Standart::clearEntered()
{
    m_UnsavedValue = '0';
    emit enteredValueChanged();
}
void Standart::clearCalculations()
{
    clearEntered();
    m_FinalValue.clear();
    m_BackEndExpression.clear();

    m_LastJoined.clear();
    m_LastOperation = Value;

    emit lastOperationChanged();
    emit enteredValueChanged();
}

void Standart::onHistoryItemClicked(HistoryElement* item)
{
    OperationElement* el = static_cast<OperationElement*>(item);

    m_FinalValue        = el->FinalValue;
    m_LastJoined        = el->LastJoined;
    m_LastOperation     = el->LastOperation;
    m_BackEndExpression = el->BackEndExpression;

    emit lastOperationChanged();
    emit finalValueChanged();
}

QString Standart::concatPHFunctionWithValue(QString const& placeHolder, double value) const
{
    QString temp = placeHolder;

    if (placeHolder.indexOf('x') != -1)
        temp.replace('x', QString::number(value), Qt::CaseSensitive);
    else
    {
        if (temp.size() == 1)
            temp = QString::number(value) + placeHolder;
        else
            temp = placeHolder + QString::number(value);
    }

    return temp;
}

QString Standart::calculateProduct()
{
    QJSValue val = m_jsEngine->evaluate(m_BackEndExpression);
    return val.toString();
}

QString const& Standart::getFinalValue() const
{
    return m_FinalValue;
}
QString const& Standart::getLastOperation() const
{
    return m_LastJoined;
}

QString OperationElement::placeHolderText() const
{
    return LastJoined + '=' + FinalValue;
}
