#include <iostream>
#include <sstream>
#include "FSM_Transition.h"
#include <iostream>
#include <sstream>



ModelDataDefinition* FSM_Transition::NewInstance(Model* model, std::string name) {
    return new FSM_Transition(model, name);
}

FSM_Transition::FSM_Transition(Model* model, std::string name) : ModelComponent(model, Util::TypeOf<FSM_Transition>(), name) {
        //_name = name;
}

PluginInformation* FSM_Transition::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<FSM_Transition>(), &FSM_Transition::LoadInstance, &FSM_Transition::NewInstance);
    info->setDescriptionHelp("//@TODO");
    //info->setAuthor("...");
    //info->setDate("...");
    //info->setObservation("...");
    return info;
}

ModelComponent* FSM_Transition::LoadInstance(Model* model, PersistenceRecord *fields) {
    FSM_Transition* newComponent = new FSM_Transition(model);
    try {
        newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
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
    return res;
}

void FSM_Transition::_onDispatchEvent(Entity* entity, unsigned int inputPortNumber){
    std::cout << "TRANSITION_CHOSEN: " << _guardExpression << std::endl; // debug
    std::cout << "BEFORE: " << "carsParked = " << _parentModel->parseExpression("carsParked") << std::endl; // debug
    _parentModel->parseExpression(getOutputActions());

    //postfire
    _parentModel->parseExpression(getSetActions());
    std::cout << "AFTER: " << "carsParked = " << _parentModel->parseExpression("carsParked") << std::endl; // debug
    std::cout << "AFTER: " << "carsParked = " << _parentModel->parseExpression("maxCarsParked") << std::endl; // debug

    auto connections = getConnections()->connections();
    auto nextState = dynamic_cast<FSM_State*>(connections->begin()->second->component);

    if (not isHistory()) {
        nextState->resetRefinment();
    }

    nextState->setMustBeImmediate();
   this->_parentModel->sendEntityToComponent(entity, nextState); 
}

std::string FSM_Transition::show(){
    return "Transition";
}

std::string trim(const std::string& str, const std::string& whitespace = " \t") {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

bool FSM_Transition::isEnabled(){
    std::cout << "GUARD_EXPRESSION: " << _guardExpression << std::endl; // debug
    if (_guardExpression == "") {
    std::cout << "TRUE" << std::endl;                                   // debug
        return true;
    }

    //auto expression_ss = std::stringstream();
    //expression_ss << _guardExpression;
    //auto actions = std::string();
    //while(std::getline(expression_ss, actions, '|')) {
    //    actions = trim(actions);
    //    auto actions_ss = std::stringstream();
    //    actions_ss << actions;
    //    if (check(actions_ss)) {
    //        return true;
    //    }
    //}

    std::cout << "FALSE" << std::endl;                                  // debug
    return false;
}

/*
bool FSM_Transition::check(std::stringstream& actions_ss) {
    auto action = std::string();
    while(std::getline(actions_ss, action, '&')) {
        action = trim(action);
        auto action_ss = std::stringstream();
        action_ss << action;
        auto operand1_str = std::string();
        auto operatorAction = std::string();
        auto operand2_str = std::string();

        std::getline(action_ss, operand1_str, ' ');
        std::getline(action_ss, operatorAction, ' ');
        std::getline(action_ss, operand2_str, ' ');

        operand1_str = trim(operand1_str);
        operatorAction = trim(operatorAction);
        operand2_str = trim(operand2_str);

        double operand1, operand2;
        try {
            operand1 = _parentModel->parseExpression(operand1_str);
            operand2 = _parentModel->parseExpression(operand2_str);
        }
        catch(const std::invalid_argument& e) {
            return false;
        }
        
        if (operatorAction == "<") {
            if (not (operand1 < operand2)) {
                return false;
            }
        } else if (operatorAction == "<=") {
            if (not (operand1 <= operand2)) {
                return false;
            }
        } else if (operatorAction == "=") {
            if (not (operand1 == operand2)) {
                return false;
            }
        } else if (operatorAction == ">") {
            if (not (operand1 > operand2)) {
                return false;
            }
        } else if (operatorAction == ">=") {
            if (not (operand1 >= operand2)) {
                return false;
            }
        }

    }
    return true;
}*/

bool FSM_Transition::_check(std::string* errorMessage){
	bool resultAll = true;
    resultAll &= _parentModel->checkExpression(_guardExpression, "Transition expression", errorMessage);
    /*resultAll &= _parentModel->checkExpression(_outputActions, "Output Action expression", errorMessage);
    resultAll &= _parentModel->checkExpression(_setActions, "Set Actions expression", errorMessage);


	if (!resultAll) {
		*errorMessage += "SearchIn was not defined.";
	}
	if (_guardExpression == "") {
         resultAll &= _parentModel->checkExpression(_guardExpression, "Transition expression", errorMessage);
		*errorMessage += "_guardExpression was not defined.";
	} else {
         resultAll &= _parentModel->checkExpression(_guardExpression, "Transition expression", errorMessage);
	}
	if (_outputActions == "") {
		resultAll = false;
		*errorMessage += "_outputActions was not defined.";
	} else {
        resultAll &= _parentModel->checkExpression(_outputActions, "Output Action expression", errorMessage);

	}*/

	return resultAll;
}


void FSM_Transition::executeActions(std::string actions){
    if (actions == "") {
        return;
    }
    auto actions_ss = std::stringstream();
    actions_ss << actions;
    auto action = std::string();

    while(std::getline(actions_ss, action, ';')) {
		_parentModel->parseExpression(action);
	}
}

void FSM_Transition::executeOutputActions() {
	executeActions(_outputActions);
}

void FSM_Transition::executeSetActions() {
	executeActions(_setActions);
}
