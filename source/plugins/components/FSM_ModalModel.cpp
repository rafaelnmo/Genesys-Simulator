#include "FSM_ModalModel.h"

ModelDataDefinition* FSM_ModalModel::NewInstance(Model* model, std::string name) {
	return new FSM_ModalModel(model, name);
}

FSM_ModalModel::FSM_ModalModel(Model* model, std::string name) : ModelComponent(model, Util::TypeOf<FSM_ModalModel>(), name) {
	_name = name;
}

PluginInformation* FSM_ModalModel::GetPluginInformation() {
	PluginInformation* info = new PluginInformation(Util::TypeOf<FSM_ModalModel>(), &FSM_ModalModel::LoadInstance, &FSM_ModalModel::NewInstance);
	info->setDescriptionHelp("//@TODO");
    //info->setAuthor("...");
	//info->setDate("...");
	//info->setObservation("...");
    return info;
}

ModelComponent* FSM_ModalModel::LoadInstance(Model* model, PersistenceRecord *fields) {
	FSM_ModalModel* newComponent = new FSM_ModalModel(model);
	try {
		newComponent->_loadInstance(fields);
	} catch (const std::exception& e) {

	}
	return newComponent;
}

void FSM_ModalModel::_saveInstance(PersistenceRecord *fields, bool saveDefaultValues) {
	fields->saveField("name", _name, "");
}

bool FSM_ModalModel::_loadInstance(PersistenceRecord *fields) {
    bool res = true;
    try {
        _name = fields->loadField("name", "");
	} catch (...) {
		res = false;
    }

    return res;
}

void FSM_ModalModel::_onDispatchEvent(Entity* entity, unsigned int inputPortNumber){
   traceSimulation(this, "I'm just a dummy model and I'll just send the entity forward");
	//this->_parentModel->sendEntityToComponent(entity, this->getConnections()->getFrontConnection()); 
}

std::string FSM_ModalModel::show(){
    return "Variable";
}
