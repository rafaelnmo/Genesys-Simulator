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
//#include "Transition.h"
//#include "State"

#ifdef PLUGINCONNECT_DYNAMIC

extern "C" StaticGetPluginInformation GetPluginInformation() {
	return &ExtendedFSM::GetPluginInformation;
}
#endif

//bool FSM_State::loadInstance(PersistenceRecord *fields) {
//    bool res = true;
//    try {
//        _name = fields->loadField("name", "");
//        //_isInitialState = fields->loadField("isInitialState", "");
//
//    }
//}

void ExtendedFSM::fire(std::string inputs) {
    //auto inputs = get_inputs(inputs_str);
    auto outputActions = std::string();
    auto setActions = std::string();
    FSM_State* destinationState;
    auto transitionFound = false;
    auto transition = _transitions->front();

    for(auto i = 0u; i < _transitions->size(); ++i){

        if (transition->getOriginState() == _current_state){
            if (parseAndCheck(transition->getGuardExpression())) {
                outputActions = transition->getOutputActions();
                setActions = transition->getSetActions();
                destinationState = transition->getDestinationState();
                transitionFound = true;
                break;
            }
        }

        transition = _transitions->next();
    }

    

    if (transitionFound) {
        // EXECUTE OUTPUT ACTIONS
        postfire(destinationState, setActions);
    }
}

void ExtendedFSM::postfire(FSM_State* destinationState, std::string setActions){
    executeActions(setActions);
    _current_state = destinationState;
}

bool ExtendedFSM::parseAndCheck(std::string expression){
    // TODO
}

void ExtendedFSM::executeActions(std::string actions){
    // TODO
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
