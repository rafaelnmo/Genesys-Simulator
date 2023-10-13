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
#include "../../kernel/util/List.h"
#include <vector>

class FSM_State : public PersistentObject_base {
public:

	FSM_State(std::string name, bool isFinalState = false, bool isInitialState = false):
		_name(name),
		// _refinementName(refinementName),
		_isInitialState(isInitialState),
		_isFinalState(isFinalState)
	{}

    bool _loadInstance(PersistenceRecord *fields);
    void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);

	void setName(std::string name) {
		_name = name;
	}

	std::string getName() const {
		return _name;
	}

	void setIsFinalState(bool isFinalState) {
		_isFinalState = isFinalState;
	}

	bool isFinalState() const {
		return _isFinalState;
	}

	void setIsInitialState(bool isInitialState) {
		_isInitialState = isInitialState;
	}

	bool isInitialState() const {
		return _isInitialState;
	}

	// void setRefinementName(std::string refinementName) {
	// 	_refinementName = refinementName;
	// }

	// std::string getRefinementName() const {
	// 	return _refinementName;
	// }

private:
	std::string _name;
	bool _isInitialState = false;
	bool _isFinalState = false;
	// std::string _refinementName;
};

class FSM_Transition : public PersistentObject_base {
public:

	// struct TransitionType {
	// 	bool isdefault = false;
	// 	bool nondeterministic = false;
	// 	bool immediatbe = false;
	// 	bool preemptive = false;
	// 	bool history = false;
	// 	bool error = false;
	// 	bool termination = false;
	// };
public:

	FSM_Transition(std::string parameterName, std::string originState, std::string destinationState, std::string guardExpression = ""):
		_originState(originState),
		_destinationState(destinationState),
		_guardExpression(guardExpression)
	{}
		// if (transitionType == nullptr)
		// 	transitionType = new TransitionType();
		// _type = transitionType;

    bool _loadInstance(PersistenceRecord *fields);
    void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);

    std::string getOriginState() {
        return _originState;
    }

    std::string getDestinationState() {
        return _destinationState;
    }

    std::string getGuardExpression() {
        return _guardExpression;
    }

    std::string getOutputActions() {
        return _outputActions;
    }

    std::string getSetActions() {
        return _setActions;
    }

private:
	std::string _guardExpression = "";
	std::string _originState;
	std::string _destinationState;
	//TransitionType* _type;
	std::string _outputActions;
	std::string _setActions = "";
};

class ExtendedFSM : public ModelDataDefinition {
public:
	ExtendedFSM(Model* model, std::string name = "");
	virtual ~ExtendedFSM() = default;
public: // static
	static ModelDataDefinition* LoadInstance(Model* model, PersistenceRecord *fields);
	static PluginInformation* GetPluginInformation();
	static ModelDataDefinition* NewInstance(Model* model, std::string name = "");
public:
	virtual std::string show();
    void fire(std::string inputs);
    void postfire(std::string destinationState, std::string setActions);
    bool parseAndCheck(std::string expression);
    void executeActions(std::string actions);
	std::string getName(){
		return _someString;
	}

    void insertState(std::string name, bool isFinalState , bool isInitialState);
    void insertTransition(std::string parameterName, std::string originState_str, std::string destinationState_str, std::string guardExpression);
protected: // must be overriden 
	virtual bool _loadInstance(PersistenceRecord *fields);
	virtual void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);
	void addState(FSM_State* state);
	void addTransition(FSM_Transition* transition);
	void fire();

protected: // could be overriden .
	virtual bool _check(std::string* errorMessage);
	virtual void _initBetweenReplications();
	virtual void _createInternalAndAttachedData();
	//virtual ParserChangesInformation* _getParserChangesInformation();
private:

	const struct DEFAULT_VALUES {
		const std::string someString = "Test";
		const unsigned int someUint = 1;
	} DEFAULT;
	std::string _someString = DEFAULT.someString;
	unsigned int _someUint = DEFAULT.someUint;
	//List<FSM_State*>* _states = new List<FSM_State*>();
	//List<FSM_Transition*>* _transitions = new List<FSM_Transition*>();
    std::vector<FSM_State> *_states = new std::vector<FSM_State>;
    std::vector<FSM_Transition> *_transitions = new std::vector<FSM_Transition>;

    std::string _currentStateName;

};

#endif /* EXFISTATMAC_H */

