/* 
 * File:   Transition.cpp
 * Author: roliveira
 *
 * Created on 4 de outubro de 2023, 01:24
 */

#include "Transition.h"
#include "../../kernel/simulator/Model.h"
#include "../../kernel/simulator/PluginManager.h"

Transition::Transition(std::string parameterName, State* originState, State* destinationState, std::string guardExpression, TransitionType* transitionType)
    : ModelDataDefinition(model, Util::TypeOf<Transition>(), name) {
    _parameterName = parameterName;
    _originState = originState;
    _destinationState = destinationState;
    _guardExpression = guardExpression;
    if (transitionType == nullptr)
        transitionType = new TransitionType();
    _type = transitionType;
}

PluginInformation* Transition::GetPluginInformation() {
    static PluginInformation info("Transition", "ModelDataDefinition", "1.0");
    // Fill in plugin information
    return &info;
}

ModelDataDefinition* Transition::LoadInstance(Model* model, PersistenceRecord* fields) {
    // Implement loading instance from PersistenceRecord
    return nullptr; // Replace with your implementation
}

ModelDataDefinition* Transition::NewInstance(Model* model, std::string name) {
    // Implement creating a new instance
    return new Transition(model, name);
}

bool Transition::_loadInstance(PersistenceRecord* fields) {
    // Implement loading instance data
    return true; // Replace with your implementation
}

void Transition::_saveInstance(PersistenceRecord* fields, bool saveDefaultValues) {
    // Implement saving instance data
}

bool Transition::_check(std::string* errorMessage) {
    // Implement custom checks and validations
    return true;
}

ParserChangesInformation* Transition::_getParserChangesInformation() {
    // Implement parser changes information
    return nullptr;
}
