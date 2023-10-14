/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   ExFiStatMac.cpp
 * Author: rlcancian
 * 
 * Created on 7 de agosto de 2022, 12:14
 */

#include "EFSM.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
//#include "Transition.h"
//#include "State"

#ifdef PLUGINCONNECT_DYNAMIC

extern "C" StaticGetPluginInformation GetPluginInformation() {
	return &ExtendedFSM::GetPluginInformation;
}
#endif

void FSM_State::_saveInstance(PersistenceRecord *fields, bool saveDefaultValues) {
	fields->saveField("name", _name, "");
}

bool FSM_State::_loadInstance(PersistenceRecord *fields) {
    bool res = true;
    try {
        _name = fields->loadField("name", "");
        //_isInitialState = fields->loadField("isInitialState", );
	} catch (...) {
		res = false;
    }
}

void FSM_Transition::_saveInstance(PersistenceRecord *fields, bool saveDefaultValues) {
    //fields->saveField("name", _name, "");
}

bool FSM_Transition::_loadInstance(PersistenceRecord *fields) {
    bool res = true;
    try {
	} catch (...) {
		res = false;
    }
}

void FSM_Variable::_saveInstance(PersistenceRecord *fields, bool saveDefaultValues) {
	fields->saveField("name", _name, "");
}

bool FSM_Variable::_loadInstance(PersistenceRecord *fields) {
    bool res = true;
    try {
        _name = fields->loadField("name", "");
	} catch (...) {
		res = false;
    }
}

std::map<std::string,int> ExtendedFSM::fire(std::map<std::string,int> inputs) {
    //auto inputs = get_inputs(inputs_str);
    std::map<std::string,int> outputActions;
    auto setActions = std::string();
    auto destinationState = std::string();
    auto transitionFound = false;
    //auto transition = _transitions->front();

    //for(auto i = 0u; i < _transitions->size(); ++i){
    //    if (transition->getOriginState() == _currentStateName){
    //        if (parseAndCheck(transition->getGuardExpression())) {
    //            outputActions = transition->getOutputActions();
    //            setActions = transition->getSetActions();
    //            destinationState = transition->getDestinationState();
    //            transitionFound = true;
    //            break;
    //        }
    //    }

    //    transition = _transitions->next();
    //}

    for (auto& transition: *_transitions) {
        if (transition.getOriginState() == _currentStateName){
            if (parseAndCheck(transition.getGuardExpression(), inputs)) {
                outputActions = getOutputValues(transition.getOutputActions());
                setActions = transition.getSetActions();
                destinationState = transition.getDestinationState();
                transitionFound = true;
                break;
            }
        }
    }
    

    if (transitionFound) {
        postfire(destinationState, setActions);
    }

    return outputActions;
}

void ExtendedFSM::postfire(std::string destinationState, std::string setActions){
    updateVariables(setActions);
    _currentStateName = destinationState;
}

std::string trim(const std::string& str, const std::string& whitespace = " \t") {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

int ExtendedFSM::getValue(std::string value_str, std::map<std::string,int> inputs = std::map<std::string,int>{}) {
    try {
        return std::stoi(value_str);
    }
    catch(const std::invalid_argument& e) {
        for (auto input: inputs) {
            if (input.first == value_str) {
                return input.second;
            }
        }
        for (auto variable: *_variables) {
            if (variable.getName() == value_str) {
                return variable._value;
            }
        }
    }
}

bool ExtendedFSM::parseAndCheck(std::string expression, std::map<std::string,int> inputs){
    if (expression == "") {
        return true;
    }
    auto expression_ss = std::stringstream();
    expression_ss << expression;
    auto action = std::string();

    while(std::getline(expression_ss, action, ';')) {
        auto action_ss = std::stringstream();
        auto operand1_str = std::string();
        auto operatorAction = std::string();
        auto operand2_str = std::string();

        std::getline(action_ss, operand1_str, ' ');
        std::getline(action_ss, operatorAction, ' ');
        std::getline(action_ss, operand2_str, ' ');

        operand1_str = trim(operand1_str);
        operatorAction = trim(operatorAction);
        operand2_str = trim(operand2_str);

        auto operand1 = getValue(operand1_str, inputs);
        auto operand2 = getValue(operand2_str, inputs);
        
        if (operatorAction == "<") {
            if (not operand1 < operand2) {
                return false;
            }
        } else if (operatorAction == "<=") {
            if (not operand1 <= operand2) {
                return false;
            }
        } else if (operatorAction == "=") {
            if (not operand1 == operand2) {
                return false;
            }
        } else if (operatorAction == ">") {
            if (not operand1 > operand2) {
                return false;
            }
        } else if (operatorAction == ">=") {
            if (not operand1 >= operand2) {
                return false;
            }
        }

    }

    return true;
}

std::map<std::string,int> ExtendedFSM::getOutputValues(std::string actions) {
    auto outputValues = std::map<std::string,int>{};
    auto actions_ss = std::stringstream();
    actions_ss << actions;
    auto action = std::string();

    while(std::getline(actions_ss, action, ';')) {
        auto action_ss = std::stringstream();
        auto outputNAME = std::string();
        auto newValue_str = std::string();

        std::getline(action_ss, outputNAME, '=');
        std::getline(action_ss, newValue_str, ';');

        auto newValue_ss = std::stringstream();
        newValue_ss << newValue_str;
        auto value_str = std::string();
        auto operatorAction = std::string();
        std::getline(newValue_ss, value_str, ' ');
        auto newValue = getValue(value_str);

        while(std::getline(newValue_ss, operatorAction, ' ')){
            std::getline(newValue_ss, value_str, ' ');
            auto value = getValue(value_str);
            if (operatorAction == "+") {
                newValue += value;
            } else if (operatorAction == "-") {
                newValue -= value;
            } else if (operatorAction == "*") {
                newValue *= value;
            } else if (operatorAction == "/") {
                newValue /= value;
            }
        }

        outputValues.insert(std::pair<std::string,int>(outputNAME, newValue));
    }

    return outputValues;
}

void ExtendedFSM::updateVariables(std::string actions){
    if (actions == "") {
        return;
    }
    auto actions_ss = std::stringstream();
    actions_ss << actions;
    auto action = std::string();

    while(std::getline(actions_ss, action, ';')) {
        auto action_ss = std::stringstream();
        auto variableNAME = std::string();
        auto newValue_str = std::string();

        std::getline(action_ss, variableNAME, '=');
        std::getline(action_ss, newValue_str, ';');

        auto newValue_ss = std::stringstream();
        newValue_ss << newValue_str;
        auto value_str = std::string();
        auto operatorAction = std::string();
        std::getline(newValue_ss, value_str, ' ');
        auto newValue = getValue(value_str);

        while(std::getline(newValue_ss, operatorAction, ' ')){
            std::getline(newValue_ss, value_str, ' ');
            auto value = getValue(value_str);
            if (operatorAction == "+") {
                newValue += value;
            } else if (operatorAction == "-") {
                newValue -= value;
            } else if (operatorAction == "*") {
                newValue *= value;
            } else if (operatorAction == "/") {
                newValue /= value;
            }
        }

        for (auto& variable: *_variables) {
            if (variable.getName() == variableNAME) {
                variable._value = newValue;
            }
        }

    }
}

void ExtendedFSM::insertState(std::string name, bool isFinalState = false, bool isInitialState = false){
    auto state = FSM_State(name, isFinalState, isInitialState);
   _states->push_back(state);
}

void ExtendedFSM::insertTransition(std::string guardExpression, std::string originState, std::string destinationState, std::string outputActions, std::string setActions){
    auto transition = FSM_Transition(guardExpression, originState, destinationState, outputActions, setActions); 
    _transitions->push_back(transition);
}

void ExtendedFSM::insertVariable(std::string name, int initialValue) {
    auto variable = FSM_Variable(name, initialValue);
}
