#include <stdexcept>
#include "FSM_State.h"

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

std::string FSM_State::show(){
    return "show";
}

void FSM_State::setAsInitialState() {
    _efsm->setCurrentState(this);
}

void FSM_State::setEFSM(ExtendedFSM* efsm) {
    _efsm = efsm;
}

void FSM_State::setRefinement(ExtendedFSM* refinement) {
    _refinement = refinement;
}

ExtendedFSM* FSM_State::getRefinement() {
    return _refinement;
}

void FSM_State::_onDispatchEvent(Entity* entity, unsigned int inputPortNumber){
	auto enableds = 0;
	auto hasDeterministicEnabled = false;
	auto hasDefaultConnected = false; // found a default to use if none is enabled
	auto connections = this->getConnections()->connections();

	auto transitionDefault = dynamic_cast<FSM_Transition*>(connections->begin()->second->component);
	auto transitionChosen = transitionDefault;

	if (transitionDefault->isDefault()) {
		hasDefaultConnected = true;
	}

	for(auto connection: *connections){
		auto transition = dynamic_cast<FSM_Transition*>(connection.second->component);
		if (not hasDefaultConnected and transition->isDefault()) {
			transitionDefault = transition;
			hasDefaultConnected = true;
		}

		if  (transition->isEnabled() and 
                (not _mustBeImmediate or 
                    (_mustBeImmediate and transition->isImmediate())
                )
            ){
			if (not transition->isNondeterministic()) {
				hasDeterministicEnabled = true;
			}
			if (not transition->isDefault()) {
				//hasNondefault = true;
				transitionChosen = transition;
			} else if (enableds <= 0 and _mustBeImmediate)
            {
                transitionChosen = transition;
            }
			++enableds;
            
		}
	}

	if (hasDeterministicEnabled and enableds > 1) {
		throw std::domain_error("More than a transition and at least one is deterministic.");
	}

    if(enableds <= 0) {
        if (_mustBeImmediate) {
            _mustBeImmediate = false;
            _efsm->leaveEFSM(entity, this);
            return;
        } else {
            transitionChosen = transitionDefault;
        }
    }
    _mustBeImmediate = false;

    if (not transitionChosen->isPreemptive()) {
        _refinement->enterEFSM(entity, transitionChosen);
    }

   this->_parentModel->sendEntityToComponent(entity, transitionChosen); 
}

