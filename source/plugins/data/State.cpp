/* 
 * File:   State.cpp
 * Author: roliveira
 *
 * Created on 4 de outubro de 2023, 01:24
 */

#include "State.h"
#include "../../kernel/simulator/Model.h"
#include "../../kernel/simulator/PluginManager.h"

State::State(Model* model, std::string name)
    : ModelDataDefinition(model, Util::TypeOf<State>(), name), _name("DefaultStateName"), _refinementName("DefaultRefinement"), _isInitialState(false), _isFinalState(false) {
    // Initialize your members here
}

std::string State::show() {
    // Implement the show() method
    return "State: " + _name;
}

PluginInformation* State::GetPluginInformation() {
    static PluginInformation info("State", "ModelDataDefinition", "1.0");
    // Fill in plugin information
    return &info;
}

ModelDataDefinition* State::LoadInstance(Model* model, PersistenceRecord* fields) {
    // Implement loading instance from PersistenceRecord
    return nullptr; // Replace with your implementation
}

ModelDataDefinition* State::NewInstance(Model* model, std::string name) {
    // Implement creating a new instance
    return new State(model, name);
}

bool State::_loadInstance(PersistenceRecord* fields) {
    // Implement loading instance data
    return true; // Replace with your implementation
}

void State::_saveInstance(PersistenceRecord* fields, bool saveDefaultValues) {
    // Implement saving instance data
}

bool State::_check(std::string* errorMessage) {
    // Implement custom checks and validations
    return true;
}

ParserChangesInformation* State::_getParserChangesInformation() {
    // Implement parser changes information
    return nullptr;
}
