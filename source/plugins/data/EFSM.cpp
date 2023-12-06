#include "EFSM.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <utility>


#ifdef PLUGINCONNECT_DYNAMIC

extern "C" StaticGetPluginInformation GetPluginInformation() {
    return &ExtendedFSM::GetPluginInformation;
}
#endif

ExtendedFSM::ExtendedFSM(Model* model, std::string name) : ModelDataDefinition(model, Util::TypeOf<ExtendedFSM>(), name) {}

std::string ExtendedFSM::show(){
   /* std::string txt = ModelDataDefinition::show() + ",assignments=[";
    for (std::list<Assignment*>::iterator it = _assignments->list()->begin(); it != _assignments->list()->end(); it++) {
        txt += (*it)->getDestination() + "=" + (*it)->getExpression() + ",";
    }
    txt = txt.substr(0, txt.length() - 1) + "]";
    return txt;*/
}

void ExtendedFSM::_createInternalAndAttachedData(){
    ModelDataManager* elems = _parentModel->getDataManager();
    
    for (Variable* variable : *_variables) {
        _attachedDataInsert(getName() + "." + variable->getName(), variable);
    }

}

void ExtendedFSM::_saveInstance(PersistenceRecord *fields, bool saveDefaultValues) {}

bool ExtendedFSM::_loadInstance(PersistenceRecord *fields) {
    bool res = true;
    try {
    } catch (...) {
        res = false;
    }

    return res;
}

PluginInformation* ExtendedFSM::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<ExtendedFSM>(), &ExtendedFSM::LoadInstance, &ExtendedFSM::NewInstance);
    return info;
}

ModelDataDefinition* ExtendedFSM::NewInstance(Model* model, std::string name) {
    return new ExtendedFSM(model, name);
}

ModelDataDefinition* ExtendedFSM::LoadInstance(Model* model, PersistenceRecord *fields) {
    ExtendedFSM* newElement = new ExtendedFSM(model);
    try {
        newElement->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newElement;
}

bool ExtendedFSM::_check(std::string* errorMessage){
    bool resultAll = true;
//    int i = 0;
//    for (auto* var: *_variables->list()) {
//        auto data = _parentModel->getDataManager()->getDataDefinition(Util::TypeOf<Variable>(), var->getName());
//            if (data == nullptr) {
//                data = _parentModel->getParentSimulator()->getPlugins()->newInstance<Variable>(_parentModel, var->getDestination());
//                _parentModel->getDataManager()->insert(data);
//            }
//    }
    return resultAll;
}

void ExtendedFSM::_initBetweenReplications(){
    _currentState = _initialState;
    for (auto* var: *_variables) {
        var->InitBetweenReplications(var);
        for (auto value: *var->getValues()) {
            std::cout << value.first + " = " + std::to_string(value.second) << std::endl;                                       // debug
            std::cout << "BEFORE_INIT: " << value.first << " = " << _parentModel->parseExpression(value.first) << std::endl;    // debug
            _parentModel->parseExpression(value.first + " = " + std::to_string(value.second));
            std::cout << "AFTER_INIT: " << value.first << " = " << _parentModel->parseExpression(value.first) << std::endl;     // debug
        }
    }
}
void ExtendedFSM::reset(){
    this->_initBetweenReplications();
}

void ExtendedFSM::insertVariable(Variable* variable) {
    _variables->push_back(variable);
}

std::string ExtendedFSM::getCurrentState(){
    return _currentState->getName();
}


void ExtendedFSM::setInitialState(FSM_State* state) {
    _initialState = state;
}

void ExtendedFSM::setCurrentState(FSM_State* state) {
    _currentState = state;
}

void ExtendedFSM::leaveEFSM(Entity* entity, FSM_State* newCurrentState) {
    setCurrentState(newCurrentState);

    auto returnComponent = _returnModels->back();
    _returnModels->pop_back();
   this->_parentModel->sendEntityToComponent(entity, returnComponent); 
}

void ExtendedFSM::enterEFSM(Entity* entity, ModelComponent* returnState) {
    _returnModels->push_back(returnState);
   this->_parentModel->sendEntityToComponent(entity, _currentState); 
}