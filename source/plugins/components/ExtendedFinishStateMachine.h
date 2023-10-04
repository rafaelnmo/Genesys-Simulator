/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   ExtendedFinishStateMachine.h
 * Author: roliveira
 *
 * Created on 4 de outubro de 2023, 01:24
 */

#ifndef EXTENDEDFINSTATMAC_H
#define EXTENDEDFINSTATMAC_H

#include "ExtendedFinishStateMachine.h"

//#include "../../kernel/simulator/Model.h"
//#include "../../kernel/simulator/Simulator.h"
//#include "../../kernel/simulator/PluginManager.h"
#include "../../kernel/simulator/ModelComponent.h"
#include "../data/State.h"
#include "../data/Transition.h"



class ExtendedFinishStateMachine : public ModelComponent {
public:
	ExtendedFinishStateMachine(Model* model, std::string name = "");
	virtual ~ExtendedFinishStateMachine() = default;
public: // virtual
	virtual std::string show();
public: // static
	static PluginInformation* GetPluginInformation();
	static ModelComponent* LoadInstance(Model* model, PersistenceRecord *fields);
	static ModelDataDefinition* NewInstance(Model* model, std::string name = "");
protected: // must be overriden 
	virtual bool _loadInstance(PersistenceRecord *fields);
	virtual void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);
	virtual void _onDispatchEvent(Entity* entity, unsigned int inputPortNumber);
protected: // could be overriden .
	virtual bool _check(std::string* errorMessage);
	virtual void _initBetweenReplications();
	virtual void _createInternalAndAttachedData();
	//virtual ParserChangesInformation* _getParserChangesInformation();
private: // methods
private: // attributes 1:1

	const struct DEFAULT_VALUES {
		const std::string someString = "Test";
		const unsigned int someUint = 1;
	} DEFAULT;
	std::string _someString = DEFAULT.someString;
	unsigned int _someUint = DEFAULT.someUint;
	
	List<State*>* _states = new List<State*>();
	List<Transition*>* _transitions = new List<Transition*>();
};

#endif /* EXTENDEDFINSTATMAC_H */

