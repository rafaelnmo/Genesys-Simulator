/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   ExFiStatMac.h
 * Author: rlcancian
 *
 * Created on 7 de agosto de 2022, 12:14
 */

#ifndef EXFISTATMAC_H
#define EXFISTATMAC_H

#include "../../kernel/simulator/ModelDataDefinition.h"
#include "../../kernel/simulator/PluginInformation.h"
//#include "../../kernel/simulator/ModelDataManager.h"
#include "../../kernel/util/List.h"
#include "../components/FSM_Transition.h"
#include "../components/FSM_State.h"
#include "../components/FSM_Variable.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

class ExtendedFSM : public ModelDataDefinition {
public: /// constructors
    ExtendedFSM(Model* model, std::string name = "");
    virtual ~ExtendedFSM() = default;

public: /// new public user methods for this component
    //std::pair<bool,std::map<std::string,int>> fire(std::map<std::string,int> inputs);
    bool fire(std::map<std::string,int> inputs, std::map<std::string,int>& outputActions);
    bool fire();

    std::vector<FSM_State*>* getStates() {
        return _states;
    }

    std::vector<FSM_Transition*>* getTransitions() {
        return _transitions;
    }

    // std::vector<FSM_Variable*>* getVariables() {
    //     return _variables;
    // }

    std::string getCurrentState(){
        return _currentState->getName();
    }

	void setCurrentState(FSM_State* state) {
		_currentState = state;
	}

    void insertNewVariable(std::string variableName, double variableValue) {
         std::cout << "VARIABLE: " << variableName << std::endl;
         std::cout << "VARIABLE VALUE: " << variableValue << std::endl;
        auto var = std::make_pair(variableName, variableValue);
        //std::cout << "VAR: " << var << std::endl;
        _variables->insert(var);
    }

    void useEFSM() {
        for(auto var: *_variables){
            _parentModel->parseExpression(var.first + "=" + std::to_string(var.second));
        }

        //_currentState = _currentState->fire();

        for(auto it = _variables->begin(); it != _variables->end(); ++it) {
            double value = _parentModel->parseExpression(it->first);
            auto var = std::make_pair(it->first, value);
            _variables->insert(it, var);
        }
    }

    //void postfire(std::string destinationState, std::string setActions, std::map<std::string,int>& inputs);
    //bool parseAndCheck(std::string expression, std::map<std::string,int>& inputs);
    //bool check(std::stringstream& expression_ss, std::map<std::string,int>& inputs);
   // void getOutputValues(std::string actions, std::map<std::string,int>& inputs, std::map<std::string,int>& outputValues);
    //void updateVariables(std::string actions, std::map<std::string,int>& inputs);
    //int getValue(std::string value_str, std::map<std::string,int> inputs);

    //void insertState(std::string name, bool isFinalState , bool isInitialState);
    //void insertTransition(std::string guardExpression, std::string originState, std::string destinationState, std::string outputActions, std::string setActions);
    //void insertVariable(std::string name, int initialValue);
    
    void insertState(FSM_State* state);
    void insertTransition(FSM_Transition* transition);
    //void insertVariable(FSM_Variable* variable);

public: /// virtual public methods
    virtual std::string show();

public: /// static public methods that must have implementations (Load and New just the same. GetInformation must provide specific infos for the new component
    static PluginInformation* GetPluginInformation();
    static ModelDataDefinition* LoadInstance(Model* model, PersistenceRecord *fields);
    static ModelDataDefinition* NewInstance(Model* model, std::string name = "");

protected: /// virtual protected method that must be overriden
    virtual bool _loadInstance(PersistenceRecord *fields);
    virtual void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);

protected: // could be overriden .
    virtual bool _check(std::string* errorMessage);
    virtual void _initBetweenReplications();
    virtual void _createInternalAndAttachedData();
    //virtual ParserChangesInformation* _getParserChangesInformation();
private:

    const struct DEFAULT_VALUES {
        const std::string someString = "Testinho";
        const unsigned int someUint = 1;
    } DEFAULT;
    std::string _someString = DEFAULT.someString;
    unsigned int _someUint = DEFAULT.someUint;
    //List<FSM_State*>* _states = new List<FSM_State*>();
    //List<FSM_Transition*>* _transitions = new List<FSM_Transition*>();
        
    std::vector<FSM_State*>* _states = new std::vector<FSM_State*>;
    std::vector<FSM_Transition*>* _transitions = new std::vector<FSM_Transition*>;
    //std::vector<FSM_Variable*>* _variables = new std::vector<FSM_Variable*>;
    std::map<std::string,double>* _variables;

    FSM_State* _currentState;

};

#endif /* EXFISTATMAC_H */

