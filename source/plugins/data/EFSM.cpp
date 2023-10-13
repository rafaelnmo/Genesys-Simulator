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

void ExtendedFSM::fire(std::string inputs) {
    //auto inputs = get_inputs(inputs_str);
    auto outputActions = std::string();
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
            if (parseAndCheck(transition.getGuardExpression())) {
                outputActions = transition.getOutputActions();
                setActions = transition.getSetActions();
                destinationState = transition.getDestinationState();
                transitionFound = true;
                break;
            }
        }
    }
    

    if (transitionFound) {
        // EXECUTE OUTPUT ACTIONS
        postfire(destinationState, setActions);
    }
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

int ExtendedFSM::getValue(std::string value_str) {
    try {
        return std::stoi(value_str);
    }
    catch(const std::invalid_argument& e) {
        for (auto variable: *_variables) {
            if (variable.getName() == value_str) {
                return variable._value;
            }
        }
    }
}

bool ExtendedFSM::parseAndCheck(std::string expression){
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

        auto operand1 = getValue(operand1_str);
        auto operand2 = getValue(operand2_str);
        
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

void ExtendedFSM::insertTransition(std::string parameterName, std::string originState_str, std::string destinationState_str, std::string guardExpression = ""){
    auto transition = FSM_Transition(parameterName, originState_str, destinationState_str, guardExpression); 
    _transitions->push_back(transition);
}

void ExtendedFSM::insertVariable(std::string name, int initialValue) {
    auto variable = FSM_Variable(name, initialValue);
}

// Rafael begin

// constructors

ModelDataDefinition* ExtendedFSM::NewInstance(Model* model, std::string name) {
	return new ExtendedFSM(model, name);
}

ExtendedFSM::ExtendedFSM(Model* model, std::string name) : ModelDataDefinition(model, Util::TypeOf<ExtendedFSM>(), name) {
}

//public

std::string ExtendedFSM::show() {
	return ModelDataDefinition::show();
}

// public static 

ModelDataDefinition* ExtendedFSM::LoadInstance(Model* model, PersistenceRecord *fields) {
	ExtendedFSM* newElement = new ExtendedFSM(model);
	try {
		newElement->_loadInstance(fields);
	} catch (const std::exception& e) {

	}
	return newElement;
}

PluginInformation* ExtendedFSM::GetPluginInformation() {
	PluginInformation* info = new PluginInformation(Util::TypeOf<ExtendedFSM>(), &ExtendedFSM::LoadInstance, &ExtendedFSM::NewInstance);
	info->setDescriptionHelp("//@TODO");

	return info;
}

// protected virtual -- must be overriden 

bool ExtendedFSM::_loadInstance(PersistenceRecord *fields) {
	bool res = ModelDataDefinition::_loadInstance(fields);
	if (res) {
		try {
			this->_someString = fields->loadField("someString", DEFAULT.someString);
			this->_someUint = fields->loadField("someUint", DEFAULT.someUint);
		} catch (...) {
		}
	}
	return res;
}

void ExtendedFSM::_saveInstance(PersistenceRecord *fields, bool saveDefaultValues) {
	ModelDataDefinition::_saveInstance(fields, saveDefaultValues);
	fields->saveField("someUint", _someUint, DEFAULT.someUint);
	fields->saveField("someString", _someString, DEFAULT.someString);
}

	void addState(FSM_State* state){

	}

	void addTransition(FSM_Transition* transition){

	}
    
	// Evaluate the guard expression.
    bool evaluateGuardExpression(const std::string& expression) {
        // Implement the logic to evaluate the expression, as previously discussed.
        // ...
    }

    // Execute output actions if the guard is true.
    void executeOutputActions(FSM_Transition* transition) {
        // Implement how to execute output actions.
        // ...
    }

    // Handle the case when no transition with a true guard is found.
    void handleNoTrueGuardCase() {
        // Implement the necessary logic for this case.
        // ...
    }


// protected virtual -- could be overriden 

//ParserChangesInformation* ExFiStatMac::_getParserChangesInformation() {}

bool ExtendedFSM::_check(std::string* errorMessage) {
	bool resultAll = true;
	resultAll &= _someString != "";
	resultAll &= _someUint > 0;
	return resultAll;
}

void ExtendedFSM::_initBetweenReplications() {
	_someString = "Test";
	_someUint = 1;
}

void ExtendedFSM::_createInternalAndAttachedData() {
	if (_reportStatistics) {
		//if (_internal == nullptr) {
		//	_internal = new StatisticsCollector(_parentModel, getName() + "." + "NumberInQueue", this); 
		//	_internelElementsInsert("NumberInQueue", _internal);
		//}
	} else { //if (_cstatNumberInQueue != nullptr) {
		this->_internalDataClear();
	}
}


// Rafael end
