/* 
 * File:   ExtendedFinishStateMachine.cpp
 * Author: roliveira
 *
 * Created on 4 de outubro de 2023, 01:24
 */


#include "ExtendedFinishStateMachine.h"
#include "../../kernel/simulator/Model.h"
#include "../../kernel/simulator/PluginManager.h"

ExtendedFinishStateMachine::ExtendedFinishStateMachine(Model* model, std::string name)
    : ModelComponent(model, Util::TypeOf<ExtendedFinishStateMachine>(), name) {
    // Initialize your members here
}

std::string ExtendedFinishStateMachine::show() {
    // Implement the show() method
    return "ExtendedFinishStateMachine";
}

PluginInformation* ExtendedFinishStateMachine::GetPluginInformation() {
	PluginInformation* info = new PluginInformation(Util::TypeOf<ExtendedFinishStateMachine>(), &ExtendedFinishStateMachine::LoadInstance, &ExtendedFinishStateMachine::NewInstance);
	info->setDescriptionHelp("//@TODO");
	return info;
}

ModelComponent* ExtendedFinishStateMachine::LoadInstance(Model* model, PersistenceRecord* fields) {
	ExtendedFinishStateMachine* newComponent = new ExtendedFinishStateMachine(model);
	try {
		newComponent->_loadInstance(fields);
	} catch (const std::exception& e) {

	}
	return newComponent;
}

ModelDataDefinition* ExtendedFinishStateMachine::NewInstance(Model* model, std::string name) {
    // Implement creating a new instance
    return new ExtendedFinishStateMachine(model, name);
}

bool ExtendedFinishStateMachine::_loadInstance(PersistenceRecord* fields) {
	bool res = ModelComponent::_loadInstance(fields);
	if (res) {
		// @TODO: not implemented yet
	}
	return res;
}

void ExtendedFinishStateMachine::_saveInstance(PersistenceRecord* fields, bool saveDefaultValues) {
    // Implement saving instance data
}

void ExtendedFinishStateMachine::_onDispatchEvent(Entity* entity, unsigned int inputPortNumber) {
    trace("I'm just a dummy model and I'll just send the entity forward");
	this->_parentModel->sendEntityToComponent(entity, this->getConnections()->getFrontConnection());
}

bool ExtendedFinishStateMachine::_check(std::string* errorMessage) {
    // Implement custom checks and validations
   	bool resultAll = true;
	resultAll &= _someString != "";
	resultAll &= _someUint > 0;
	return resultAll;
}

void ExtendedFinishStateMachine::_initBetweenReplications() {
    // Implement initialization logic between replications
    _someString = "Test";
	_someUint = 1;
}

void ExtendedFinishStateMachine::_createInternalAndAttachedData() {
    // Implement creating internal and attached data
}
