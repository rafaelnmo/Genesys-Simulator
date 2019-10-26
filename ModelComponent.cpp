/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Element.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 21 de Junho de 2018, 15:56
 */

#include "ModelComponent.h"
#include "Model.h"

ModelComponent::ModelComponent(Model* model, std::string componentTypename) : ModelElement(model, componentTypename, false) {
    //_parentModel = model;
    model->components()->insert(this);
}

ModelComponent::~ModelComponent(){
    _parentModel->components()->remove(this);
}

void ModelComponent::Execute(Entity* entity, ModelComponent* component, unsigned int inputNumber) {
    std::string msg = "Entity " + std::to_string(entity->getEntityNumber()) + " has arrived at component \"" + component->_name + "\"";
    //TODO: How can I know the number of inputs?
    if (inputNumber > 0)
	msg += " by input " + std::to_string(inputNumber);
    component->_parentModel->tracer()->trace(Util::TraceLevel::blockArrival, msg);
    Util::IncIndent();
    try {
	component->_execute(entity);
    } catch (const std::exception& e) {
	component->_parentModel->tracer()->traceError(e, "Error executing component " + component->show());
    }
    Util::DecIndent();
}

void ModelComponent::InitBetweenReplications(ModelComponent* component) {
    //component->_model->getTraceManager()->trace(Util::TraceLevel::blockArrival, "Writing component \"" + component->_name + "\""); //std::to_string(component->_id));
    try {
	component->_initBetweenReplications();
    } catch (const std::exception& e) {
	component->_parentModel->tracer()->traceError(e, "Error initing component " + component->show());
    };
}

void ModelComponent::CreateInternalElements(ModelComponent* component) {
    //component->_model->getTraceManager()->trace(Util::TraceLevel::blockArrival, "Writing component \"" + component->_name + "\""); //std::to_string(component->_id));
    try {
	component->_createInternalElements();
    } catch (const std::exception& e) {
	component->_parentModel->tracer()->traceError(e, "Error creating elements of component " + component->show());
    };    
}

std::map<std::string, std::string>* ModelComponent::SaveInstance(ModelComponent* component) {
    component->_parentModel->tracer()->trace(Util::TraceLevel::mostDetailed, "Writing component \"" + component->_name + "\""); //std::to_string(component->_id));
    std::map<std::string, std::string>* fields = new std::map<std::string, std::string>();
    try {
	fields = component->_saveInstance();
    } catch (const std::exception& e) {
	component->_parentModel->tracer()->traceError(e, "Error executing component " + component->show());
    }
    return fields;
}

bool ModelComponent::Check(ModelComponent* component) {
    component->_parentModel->tracer()->trace(Util::TraceLevel::mostDetailed, "Checking " + component->_typename + ": " + component->_name); //std::to_string(component->_id));
    bool res = false;
    std::string* errorMessage = new std::string();
    Util::IncIndent();
    {
	try {
	    res = component->_check(errorMessage);
	    if (!res) {
		component->_parentModel->tracer()->trace(Util::TraceLevel::errors, "Error: Checking has failed with message '" + *errorMessage + "'");
	    }
	} catch (const std::exception& e) {
	    component->_parentModel->tracer()->traceError(e, "Error verifying component " + component->show());
	}
    }
    Util::DecIndent();
    return res;
}

ConnectionManager* ModelComponent::nextComponents() const {
    return _nextComponents;
}

std::string ModelComponent::show() {
    return ModelElement::show(); // "{id=" + std::to_string(this->_id) + ",name=\""+this->_name + "\"}"; // , nextComponents[]=(" + _nextComponents->show() + ")}";
}

bool ModelComponent::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelElement::_loadInstance(fields);
    if (res) {
	// Now it should load nextComponents. The problem is that the nextCOmponent may not be loaded yet.
	// So, what can be done is to temporarily load the ID of the nextComponents, and to wait until all the components have been loaded to update nextComponents based on the temporarilyIDs now being loaded
	//unsigned short nextSize = std::stoi((*fields->find("nextSize")).second);
	//this->_tempLoadNextComponentsIDs = new List<Util::identification>();
	//for (unsigned short i = 0; i < nextSize; i++) {
	//    Util::identification nextId = std::stoi((*fields->find("nextId" + std::to_string(i))).second);
	//    this->_tempLoadNextComponentsIDs->insert(nextId);
	//}
    }
    return res;
}

std::map<std::string, std::string>* ModelComponent::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelElement::_saveInstance();
    fields->emplace("nextSize", std::to_string(this->_nextComponents->size()));
    unsigned short i = 0;
    for (std::list<Connection*>::iterator it = _nextComponents->list()->begin(); it != _nextComponents->list()->end(); it++) {
	fields->emplace("nextId" + std::to_string(i), std::to_string((*it)->first->_id));
	fields->emplace("nextInputNumber" + std::to_string(i), std::to_string((*it)->second));
	i++;
    }
    return fields;
}

void ModelComponent::_createInternalElements() {
    
}

/*
std::list<std::map<std::string,std::string>*>* ModelComponent::_saveInstance(std::string type) {
    std::list<std::map<std::string,std::string>*>* fields = ModelComponent::_saveInstance();
    fields->push_back(std::to_string(this->_nextComponents->size()));
    for (std::list<ModelComponent*>::iterator it=_nextgetComponentManager()->begin(); it!=_nextgetComponentManager()->end(); it++){
	fields->push_back((*it)->_name);
    }
    return fields;
}
 */