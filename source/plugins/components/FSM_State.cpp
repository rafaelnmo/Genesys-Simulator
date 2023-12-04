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

std::string FSM_State::show(){
    return "show";
}

void FSM_State::_onDispatchEvent(Entity* entity, unsigned int inputPortNumber){}

void FSM_State::setAsInitialState() {
    _efsm->setCurrentState(this);
}

void FSM_State::setRefinementName(ExtendedFSM* refinement) {
    _refinement = refinement;
}

void FSM_State::fire(Entity* entity, bool mustBeImmediate){
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
                (not mustBeImmediate or 
                    (mustBeImmediate and transition->isImmediate())
                )
            ){
			if (not transition->isNondeterministic()) {
				hasDeterministicEnabled = true;
			}
			if (not transition->isDefault()) {
				//hasNondefault = true;
				transitionChosen = transition;
			} else if (enableds <= 0 and mustBeImmediate)
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
        if (mustBeImmediate) {
            _efsm->setCurrentState(this);
            return;
        } else {
            transitionChosen = transitionDefault;
        }
    }

    if (not transitionChosen->isPreemptive()) {
        _refinement->useEFSM(entity);
    }

    //_parentModel->parseExpression(transitionChosen->getOutputActions());

    //postfire
    //_parentModel->parseExpression(transitionChosen->getSetActions());

    connections = transitionChosen->getConnections()->connections();
    auto nextState = dynamic_cast<FSM_State*>(connections->begin()->second->component);

    if (not transitionChosen->isHistory()) {
        nextState->_refinement->reset();
    }

    nextState->fire(entity, true);
    //return stateDestination; //->fire(true);
}

