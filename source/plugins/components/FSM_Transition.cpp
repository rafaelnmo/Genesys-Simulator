#include "FSM_Transition.h"



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
}

void FSM_Transition::_onDispatchEvent(Entity* entity, unsigned int inputPortNumber){
    traceSimulation(this, "I'm just a dummy model and I'll just send the entity forward");
	//this->_parentModel->sendEntityToComponent(entity, this->getConnections()->getFrontConnection());
}

std::string FSM_Transition::show(){
    return "Transition";
}
