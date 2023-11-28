#include "EFSM.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <utility>


#ifdef PLUGINCONNECT_DYNAMIC

extern "C" StaticGetPluginInformation GetPluginInformation() {
    return &ExtendedFSM::GetPluginInformation;
}
#endif


bool ExtendedFSM::fire(std::map<std::string,int> inputs, std::map<std::string,int>& outputActions) {
    for (auto state: *_states) {
        if (state->getName() == _currentStateName and state->isFinalState()){
            return true;
        }
    }
    
    auto setActions = std::string();
    auto destinationState = std::string();
    auto transitionFound = false;

    for (auto& transition: *_transitions) {
        if (transition->getOriginState() == _currentStateName){
            if (parseAndCheck(transition->getGuardExpression(), inputs)) {
                getOutputValues(transition->getOutputActions(), inputs, outputActions);
                setActions = transition->getSetActions();
                destinationState = transition->getDestinationState();
                transitionFound = true;
                break;
            }
        }
    }
    

    if (transitionFound) {
        postfire(destinationState, setActions, inputs);
    }

    return false;
}

bool ExtendedFSM::fire() {
    auto inputs = std::map<std::string,int>{};
    auto outputActions = std::map<std::string,int>{};

    return fire(inputs, outputActions);
}

void ExtendedFSM::postfire(std::string destinationState, std::string setActions, std::map<std::string,int>& inputs){
    updateVariables(setActions, inputs);
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

void print(std::string name, std::string value){
    std::cout << name <<": " << value << std::endl;
}

int ExtendedFSM::getValue(std::string value_str, std::map<std::string,int> inputs) {
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
            if (variable->getName() == value_str) {
                return variable->_value;
            }
        }

        throw std::invalid_argument(value_str + " not found!");
    }
}

bool ExtendedFSM::parseAndCheck(std::string expression, std::map<std::string,int>& inputs){
    if (expression == "") {
        return true;
    }

    auto expression_ss = std::stringstream();
    expression_ss << expression;
    auto actions = std::string();
    while(std::getline(expression_ss, actions, '|')) {
        actions = trim(actions);
        auto actions_ss = std::stringstream();
        actions_ss << actions;
        if (check(actions_ss, inputs)) {
            return true;
        }
    }

    return false;
}

bool ExtendedFSM::check(std::stringstream& actions_ss, std::map<std::string,int>& inputs) {
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

        int operand1, operand2;
        try {
            operand1 = getValue(operand1_str, inputs);
            operand2 = getValue(operand2_str, inputs);
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
}

void ExtendedFSM::getOutputValues(std::string actions, std::map<std::string,int>& inputs, std::map<std::string,int>& outputValues) {
    auto actions_ss = std::stringstream();
    actions_ss << actions;
    auto action = std::string();

    while(std::getline(actions_ss, action, ';')) {
        auto action_ss = std::stringstream();
        action_ss << action;
        auto outputNAME = std::string();
        auto newValue_str = std::string();

        std::getline(action_ss, outputNAME, '=');
        std::getline(action_ss, newValue_str, ';');
        outputNAME = trim(outputNAME);
        newValue_str = trim(newValue_str);

        auto newValue_ss = std::stringstream();
        newValue_ss << newValue_str;
        auto value_str = std::string();
        auto operatorAction = std::string();
        std::getline(newValue_ss, value_str, ' ');
        try {
            auto newValue = getValue(value_str, inputs);
            while(std::getline(newValue_ss, operatorAction, ' ')){
                std::getline(newValue_ss, value_str, ' ');
                auto value = getValue(value_str, inputs);
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
        catch(const std::invalid_argument& e) {
            outputValues.insert(std::pair<std::string,int>(e.what(), -1));
        }
    }
}

void ExtendedFSM::updateVariables(std::string actions, std::map<std::string,int>& inputs){
    if (actions == "") {
        return;
    }
    auto actions_ss = std::stringstream();
    actions_ss << actions;
    auto action = std::string();

    while(std::getline(actions_ss, action, ';')) {
        auto action_ss = std::stringstream();
        action_ss << action;
        auto variableNAME = std::string();
        auto newValue_str = std::string();

        std::getline(action_ss, variableNAME, '=');
        std::getline(action_ss, newValue_str, ';');
        variableNAME = trim(variableNAME);
        newValue_str = trim(newValue_str);



        auto newValue_ss = std::stringstream();
        newValue_ss << newValue_str;
        auto value_str = std::string();
        auto operatorAction = std::string();
        std::getline(newValue_ss, value_str, ' ');
        auto newValue = getValue(value_str, inputs);

        while(std::getline(newValue_ss, operatorAction, ' ')){
            std::getline(newValue_ss, value_str, ' ');
            auto value = getValue(value_str, inputs);
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
            if (variable->getName() == variableNAME) {
                variable->_value = newValue;
            }
        }

    }
}
/*
void ExtendedFSM::insertState(std::string name, bool isFinalState = false, bool isInitialState = false){
    if (isInitialState) {
        _currentStateName = name;
    }
    //auto state = FSM_State(name, isFinalState, isInitialState);
    auto state = FSM_State(_parentModel, name);
    state.setIsFinalState(isFinalState);
    state.setIsInitialState(isInitialState);
   _states->push_back(state);
}*/

/*void ExtendedFSM::insertTransition(std::string guardExpression, std::string originState, std::string destinationState, std::string outputActions, std::string setActions){
    //auto transition = FSM_Transition(guardExpression, originState, destinationState, outputActions, setActions);
    //auto transition = FSM_Transition(guardExpression, originState, destinationState, outputActions, setActions);  
    auto transition = FSM_Transition(_parentModel, "");

    //std::cout << "transition: " << transition <<"\n";
    _transitions->push_back(transition);
}*/
/*
void ExtendedFSM::insertVariable(std::string name, int initialValue) {
    //auto variable = FSM_Variable(name, initialValue);
    auto variable = FSM_Variable(_parentModel, name);
    variable.setInitialValue(initialValue);
    _variables->push_back(variable);
}*/
/*
void ExtendedFSM::insertVariable(FSM_Variable* variable) {
    std::cout << "VARIABLE NAME: " << variable->getName() << "\n";
    std::cout << "VARIABLE SIZE BEFORE: " << _variables->size() << "\n";

    _variables->push_back(variable);
    std::cout << "VARIABLE SIZE AFTER: " << _variables->size() << "\n";

}*/

std::string ExtendedFSM::show(){
    return "ExtendedFSM";
}

bool ExtendedFSM::_check(std::string* errorMessage){
    bool resultAll = true;
    *errorMessage += "";
    return resultAll;
}

void ExtendedFSM::_initBetweenReplications(){}

void ExtendedFSM::_createInternalAndAttachedData(){
    ModelDataManager* elems = _parentModel->getDataManager();
	for (Assignment* ass : *_assignments->list()) {
		ModelDataDefinition* elem;
		std::string name;
		if (ass->isAttributeNotVariable()) {
			name = "Attribute";
			elem = elems->getDataDefinition(Util::TypeOf<Attribute>(), ass->getDestination());
		} else {
			name = "Variable";
			elem = elems->getDataDefinition(Util::TypeOf<Variable>(), ass->getDestination());
		}
		//assert elem != nullptr
		if (elem != nullptr) {
			this->_attachedDataInsert(name + "_" + ass->getDestination(), elem);
		}
	}

}

void ExtendedFSM::_saveInstance(PersistenceRecord *fields, bool saveDefaultValues) {}

bool ExtendedFSM::_loadInstance(PersistenceRecord *fields) {
    bool res = true;
    try {
    } catch (...) {
        res = false;
    }

    return res;
}

PluginInformation* ExtendedFSM::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<ExtendedFSM>(), &ExtendedFSM::LoadInstance, &ExtendedFSM::NewInstance);
    return info;
}

ModelDataDefinition* ExtendedFSM::NewInstance(Model* model, std::string name) {
    return new ExtendedFSM(model, name);
}

ModelDataDefinition* ExtendedFSM::LoadInstance(Model* model, PersistenceRecord *fields) {
    ExtendedFSM* newElement = new ExtendedFSM(model);
    try {
        newElement->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newElement;
}

ExtendedFSM::ExtendedFSM(Model* model, std::string name) : ModelDataDefinition(model, Util::TypeOf<ExtendedFSM>(), name) {
    //_elems = elems;
}

void ExtendedFSM::useEFSM() {
    for(auto var: *_variables){
        _parentModel->parseExpression(var.first + "=" + std::to_string(var.second));
    }

    _currentState = _currentState->fire();

    for(auto it = _variables->begin(); it != _variables->end(); ++it) {
        double value = _parentModel->parseExpression(it->first);
        auto var = std::make_pair(it->first, value);
        _variables->insert(it, var);
    }
}
