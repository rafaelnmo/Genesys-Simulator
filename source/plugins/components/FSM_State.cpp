#include "FSM_State.h"


ModelDataDefinition* FSM_State::NewInstance(Model* model, std::string name) {
	return new FSM_State(model, name);
}

FSM_State::FSM_State(Model* model, std::string name) : ModelComponent(model, Util::TypeOf<FSM_State>(), name) {
}

PluginInformation* FSM_State::GetPluginInformation() {
	PluginInformation* info = new PluginInformation(Util::TypeOf<FSM_State>(), &FSM_State::LoadInstance, &FSM_State::NewInstance);
	info->setDescriptionHelp("//@TODO");
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
