#include "FSM_Variable.h"


ModelDataDefinition* FSM_Variable::NewInstance(Model* model, std::string name) {
	return new FSM_Variable(model, name);
}

FSM_Variable::FSM_Variable(Model* model, std::string name) : ModelComponent(model, Util::TypeOf<FSM_Variable>(), name) {
}

PluginInformation* FSM_Variable::GetPluginInformation() {
	PluginInformation* info = new PluginInformation(Util::TypeOf<FSM_Variable>(), &FSM_Variable::LoadInstance, &FSM_Variable::NewInstance);
	info->setDescriptionHelp("//@TODO");
    //info->setAuthor("...");
	//info->setDate("...");
	//info->setObservation("...");
    return info;
}

ModelComponent* FSM_Variable::LoadInstance(Model* model, PersistenceRecord *fields) {
	FSM_Variable* newComponent = new FSM_Variable(model);
	try {
		newComponent->_loadInstance(fields);
	} catch (const std::exception& e) {

	}
	return newComponent;
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

    return res;
}

void FSM_Variable::_onDispatchEvent(Entity* entity, unsigned int inputPortNumber){
   traceSimulation(this, "I'm just a dummy model and I'll just send the entity forward");
	this->_parentModel->sendEntityToComponent(entity, this->getConnections()->getFrontConnection()); 
}

std::string FSM_Variable::show(){
    return "Variable";
}
