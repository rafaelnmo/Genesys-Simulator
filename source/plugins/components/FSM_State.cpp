#include <stdexcept>
#include "FSM_State.h"
#include "../data/EFSM.h"

ModelDataDefinition* FSM_State::NewInstance(Model* model, std::string name) {
	return new FSM_State(model, name);
}

FSM_State::FSM_State(Model* model, std::string name) : ModelComponent(model, Util::TypeOf<FSM_State>(), name) {
	_name = name;
	//std::cout << "STATE CONSTRUCTOR" << "\n";
}

PluginInformation* FSM_State::GetPluginInformation() {
	PluginInformation* info = new PluginInformation(Util::TypeOf<FSM_State>(), &FSM_State::LoadInstance, &FSM_State::NewInstance);
	info->setDescriptionHelp("//@TODO");
	info->setReceiveTransfer(true);
	info->setSendTransfer(true);
    //info->setAuthor("...");
	//info->setDate("...");
	//info->setObservation("...");
    return info;
}

ModelComponent* FSM_State::LoadInstance(Model* model, PersistenceRecord *fields) {
	FSM_State* newComponent = new FSM_State(model);
	try {
		newComponent->_loadInstance(fields);
	} catch (const std::exception& e) {

	}
	return newComponent;
}

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

    return res;
}
void FSM_State::_onDispatchEvent(Entity* entity, unsigned int inputPortNumber){
    traceSimulation(this, "I'm just a dummy model and I'll just send the entity forward");
	//this->_parentModel->sendEntityToComponent(entity, this->getConnections()->getFrontConnection());
}

std::string FSM_State::show(){
    return "show";
}

void FSM_State::setIsInitialState(bool isInitialState) {
    _efsm->setCurrentState(this);
    //_isInitialState = isInitialState;
}

FSM_State* FSM_State::fire(bool mustBeImmediate){
	//FSM_Transition let;
	//auto enableds = std::vector<FSM_Transition*>{};
	auto enableds = 0;
	auto hasDeterministic = false;
	//auto hasNondefault = false; // to ignore default
	auto hasDefault = false; // found a default to use if none is enabled
	auto connections = this->getConnections()->connections();

	auto transitionDefault = dynamic_cast<FSM_Transition*>(connections->begin()->second->component);
	auto transitionChosen = transitionDefault;

	if (transitionDefault->isDefault()) {
		hasDefault = true;
	}
	for(auto connection: *connections){
		auto transition = dynamic_cast<FSM_Transition*>(connection.second->component);
		if (not hasDefault and transition->isDefault()) {
			transitionDefault = transition;
			hasDefault = true;
		}

		if (transition->isEnabled()) {
			//enableds.push_back(transition);
			++enableds;
			if (not transition->isNondeterministic()) {
				hasDeterministic = true;
			}
			if (not transition->isDefault()) {
				//hasNondefault = true;
				transitionChosen = transition;
			}
		}
	}

	if (hasDeterministic and enableds > 1) {
		throw std::domain_error("More than a transition and at least one is deterministic.");
	}

	if (enableds <= 0) {
		transitionChosen = transitionDefault;
	}
/*
	if (not transitionChosen->isPreemptive()) {
		_refinementName->useEFSM();
	}
*/
	//_parentModel->parseExpression(transitionChosen->getOutputActions());

	//postfire
	//_parentModel->parseExpression(transitionChosen->getSetActions());

	connections = transitionChosen->getConnections()->connections();
	auto stateDestination = dynamic_cast<FSM_State*>(connections->begin()->second->component);
	return stateDestination; //->fire(true);
}

