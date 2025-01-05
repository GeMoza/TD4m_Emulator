// Commands/Commands.h

#pragma once

#include "../Logging/Logger.h"
#include "../Config/config.h"
#include "CommandBase.h"

using namespace System;

/* Операция присваивания с влиянием на флаги reg ⇐ v1 + v2 + v3
* Варианты:
*           Присваивание значения
*           Присваивание суммы двух значений
*           Присваивание суммы трех значений
*/
public ref class CommandMAD : public Command {
public:
    CommandMAD(Registers^ reg, Memory^ mem, Logger^ log) : Command(reg, mem, log) {}

    virtual void Execute() override {
        registers->PC++;

        logger->Log("CommandMAD: Default Execute method called. No specific operation defined.");
    }

    void Execute(Byte^ target, Byte^ operand) override {
        if (target == nullptr || operand == nullptr) {
            logger->LogAndThrow("Operands", "Operands cannot be null");
        }

        *target = *operand;

        // Обновление флагов
        registers->Z = (*target == 0);
        registers->C = false;
        registers->PC++;

        logger->Log(String::Format("CommandMAD: MOV operation executed. Target={0}, Operand={1}", *target, *operand));
    }

    void Execute(Byte^ target, Byte^ operand1, Byte^ operand2) override {
        if (target == nullptr || operand1 == nullptr || operand2 == nullptr) {
            logger->LogAndThrow("Operands", "Operands cannot be null");
        }

        int result = *operand1 + *operand2;
        *target = static_cast<Byte>(result & 0xF);

        // Обновление флагов
        registers->Z = (*target == 0);
        registers->C = (result > 0xF);
        registers->PC++;

        logger->Log(String::Format("CommandMAD: ADD operation executed. Target={0}, Operand1={1}, Operand2={2}", *target, *operand1, *operand2));
    }

    void Execute(Byte^ target, Byte^ operand1, Byte^ operand2, Byte^ operand3) override {
        if (target == nullptr || operand1 == nullptr || operand2 == nullptr || operand3 == nullptr) {
            logger->LogAndThrow("Operands", "Operands cannot be null");
        }

        int result = *operand1 + *operand2 + *operand3;
        *target = static_cast<Byte>(result & 0xF);

        // Обновление флагов
        registers->Z = (*target == 0);
        registers->C = (result > 0xF);
        registers->PC++;

        logger->Log(String::Format("CommandMAD: ADD operation executed. Target={0}, Operand1={1}, Operand2={2}, Operand3={3}", *target, *operand1, *operand2, *operand3));
    }
};


/* Операция присваивания без влиянием на флаги reg ⇐ v1
* Варианты:
*           Присваивание значения при выполнении условия
*           Присваивание значения
*/
public ref class CommandMNA : public Command {
public:
    CommandMNA(Registers^ reg, Memory^ mem, Logger^ log) : Command(reg, mem, log) {}

    virtual void Execute() override {
        registers->PC++;

        logger->Log("CommandMAD: Default Execute method called. No specific operation defined.");
    }

    // С условием
    void Execute(Byte^ target, Byte value, Func<bool>^ condition) {
        if (condition == nullptr || condition()) {
            *target = value;
            logger->Log(String::Format("CommandMNA: Value {0} assigned to target", value));
        }
        else {
            registers->PC++;
            logger->Log("CommandMNA: Condition not met, assignment skipped.");
        }
    }

    // Без условия
    void Execute(Byte^ target, Byte value) {
        *target = value;
        logger->Log(String::Format("CommandMNA: Value {0} assigned to target", value));
    }
};


/* Операции с отрицанием и вычитанием (A ⇐ -A и A ⇐ A - B)
* Варианты:
*           Отрицание значения
*           Вычитание двух значений
*/
public ref class CommandNegSub : public Command {
public:
    CommandNegSub(Registers^ reg, Memory^ mem, Logger^ log) : Command(reg, mem, log) {}

    virtual void Execute() override {
        registers->PC++;

        logger->Log("CommandMAD: Default Execute method called. No specific operation defined.");
    }

    // Отрицание значения
    void ExecuteNeg(Byte^ target) {
        if (target == nullptr) {
            logger->LogAndThrow("Operands", "Target cannot be null");
        }

        *target = (~(*target) + 1) & 0xF;

        // Обновление флагов
        registers->Z = (*target == 0);
        registers->C = false;
        registers->PC++;

        logger->Log(String::Format("CommandNegSub: Negation executed. Target={0}", *target));
    }

    // Вычитание двух значений
    void ExecuteSub(Byte^ target, Byte^ operand) {
        if (target == nullptr || operand == nullptr) {
            logger->LogAndThrow("Operands", "Operands cannot be null");
        }

        int result = *target + (~(*operand) + 1);
        *target = static_cast<Byte>(result & 0xF);

        // Обновление флагов
        registers->Z = (*target == 0);
        registers->C = (result < 0);
        registers->PC++;

        logger->Log(String::Format("CommandNegSub: Subtraction executed. Target={0}, Operand={1}", *target, *operand));
    }
};


/* Логические операции (A ⇐ NOT A, A ⇐ A OR B, A ⇐ A AND B, A ⇐ A XOR B)
* Варианты:
*           NOT
*           OR
*           AND
*           XOR
*/

// Перечисление для логических операций
enum class LogicOperation {
    NOT,
    OR,
    AND,
    XOR
};

public ref class CommandLogic : public Command {
public:
    CommandLogic(Registers^ reg, Memory^ mem, Logger^ log) : Command(reg, mem, log) {}

    virtual void Execute() override {
        registers->PC++;

        logger->Log("CommandMAD: Default Execute method called. No specific operation defined.");
    }

    // Логическое отрицание A ⇐ NOT A
    void Execute(Byte^ target) {
        if (target == nullptr) {
            logger->LogAndThrow("Operands", "Target cannot be null");
        }

        *target = ~(*target) & 0xF;

        // Обновление флагов
        registers->Z = (*target == 0);
        registers->C = false;
        registers->PC++;

        logger->Log(String::Format("CommandLogic: NOT operation executed. Target={0}", *target));
    }

    // Логические операции A ⇐ A OR/AND/XOR B
    void Execute(Byte^ target, Byte^ operand, LogicOperation operation) {
        if (target == nullptr || (operation != LogicOperation::NOT && operand == nullptr)) {
            logger->LogAndThrow("Operands", "Operands cannot be null");
        }

        switch (operation) {
        case LogicOperation::NOT:
            *target = ~(*target) & 0xF;
            break;
        case LogicOperation::OR:
            *target = (*target | *operand) & 0xF;
            break;
        case LogicOperation::AND:
            *target = (*target & *operand) & 0xF;
            break;
        case LogicOperation::XOR:
            *target = (*target ^ *operand) & 0xF;
            break;
        default:
            logger->LogAndThrow("Operation", "Unsupported operation");
        }

        // Обновление флагов
        registers->Z = (*target == 0);
        registers->C = false;
        registers->PC++;

        logger->Log(String::Format("CommandLogic: {0} operation executed. Target={1}, Operand={2}", operation.ToString(), *target, operand != nullptr ? *operand : 0));
    }
};
