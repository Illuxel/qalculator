#include "Calculator.hpp"

#include "OperationHistory.hpp"
#include "Utils.hpp"

Standart::Standart(QObject* parent)
    : QObject{ parent }
    , m_jsEngine(new QJSEngine(this))
{
    m_UnsavedValue  = '0';
    m_LastOperation = Value;
}
Standart::~Standart()
{
    delete m_jsEngine;
}

void Standart::processButton(QString const& type, QString const& func, QString const& placeHolder)
{
    QString capitalized = type;
    capitalized[0]      = type[0].toUpper();
    WaitOperation t     = ConvertStringToEnum<WaitOperation>(capitalized);

    switch (t)
    {
        case Standart::Cmd:      ExecuteCommand(func); break;
        case Standart::Function: AddFunction(func, placeHolder); break;
        case Standart::Operator: AddOperator(*func.begin()); break;
        case Standart::Value:    AddEnteredValue(*func.begin()); break;
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

    m_FinalValue = CalculateProduct();
    emit finalValueChanged();

    OperationElement* el = new OperationElement();

    el->SetFinalValue(m_FinalValue);

    el->SetUnsavedValue(m_UnsavedValue);
    m_UnsavedValue.clear();

    m_LastJoined = m_BackEndExpression;
    el->SetLastJoined(m_LastJoined);
    emit lastOperationChanged();

    el->SetBackEndExpression(m_BackEndExpression);
    el->SetOperationType(m_LastOperation);

    m_History->pushElement(el);
}

void Standart::ExecuteCommand(QString const& cmd)
{
    Command c = ConvertStringToEnum<Command>(cmd);

    switch (c)
    {
        case Standart::del:    DeleteEnteredValue(); break;
        case Standart::clr:    ClearEntered(); break;
        case Standart::clrall: ClearCalculations(); break;
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

Q_INVOKABLE void Standart::SetEnteredValue(QString const& value)
{
    m_UnsavedValue  = value;
    m_LastOperation = Value;

    emit enteredValueChanged();
}
void Standart::AddEnteredValue(QChar const& value)
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

void Standart::AddOperator(QChar const& op)
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
void Standart::AddFunction(QString const& func, QString const& placeHolder)  // Math.pow(%1, 2)
{
    /*if (m_LastOperation == Undefined)
            return;*/

    if (m_LastOperation == Function)
    {
        m_BackEndExpression = func.arg(m_FinalValue);
        m_LastJoined        = ConcatPHFunctionWithValue(placeHolder, m_FinalValue.toDouble());
        m_FinalValue        = CalculateProduct();
        m_UnsavedValue      = m_FinalValue;

        m_LastOperation = Function;

        OperationElement* el = new OperationElement();

        el->SetFinalValue(m_FinalValue);
        el->SetUnsavedValue(m_UnsavedValue);
        el->SetLastJoined(m_LastJoined);
        el->SetBackEndExpression(m_BackEndExpression);
        el->SetOperationType(m_LastOperation);

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
    m_FinalValue        = CalculateProduct();

    m_LastJoined    = ConcatPHFunctionWithValue(placeHolder, m_UnsavedValue.toDouble());
    m_LastOperation = Function;

    OperationElement* el = new OperationElement();

    el->SetFinalValue(m_FinalValue);
    el->SetUnsavedValue(m_UnsavedValue);
    el->SetLastJoined(m_LastJoined);
    el->SetBackEndExpression(m_BackEndExpression);
    el->SetOperationType(m_LastOperation);

    m_History->pushElement(el);

    emit lastOperationChanged();
    emit finalValueChanged();
}

void Standart::DeleteEnteredValue()
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

void Standart::ClearEntered()
{
    m_UnsavedValue = '0';
    emit enteredValueChanged();
}
void Standart::ClearCalculations()
{
    ClearEntered();
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

    m_FinalValue = el->GetFinalValue();
    m_LastJoined = el->GetLastJoined();

    m_LastOperation     = el->GetOperationType();
    m_BackEndExpression = el->GetBackEndExpression();

    emit lastOperationChanged();
    emit finalValueChanged();
}

QString Standart::ConcatPHFunctionWithValue(QString const& placeHolder, double value) const
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

QString Standart::CalculateProduct()
{
    QJSValue val = m_jsEngine->evaluate(m_BackEndExpression);
    return val.toString();
}

QString const& Standart::GetFinalValue() const
{
    return m_FinalValue;
}
QString const& Standart::GetLastOperation() const
{
    return m_LastJoined;
}

QString OperationElement::placeHolderText() const
{
    return LastJoined + '=' + FinalValue;
}

QString const& OperationElement::GetFinalValue() const
{
    return FinalValue;
}
void OperationElement::SetFinalValue(QString val)
{
    FinalValue = val;
}

QString const& OperationElement::GetUnsavedValue() const
{
    return UnsavedValue;
}
void OperationElement::SetUnsavedValue(QString val)
{
    UnsavedValue = val;
}

QString const& OperationElement::GetLastJoined() const
{
    return LastJoined;
}
void OperationElement::SetLastJoined(QString val)
{
    LastJoined = val;
}

QString const& OperationElement::GetBackEndExpression() const
{
    return BackEndExpression;
}
void OperationElement::SetBackEndExpression(QString val)
{
    BackEndExpression = val;
}

Standart::WaitOperation OperationElement::GetOperationType() const
{
    return LastOperation;
}
void OperationElement::SetOperationType(Standart::WaitOperation val)
{
    LastOperation = val;
}
