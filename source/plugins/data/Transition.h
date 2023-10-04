/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/*
 * File:   Transition.h
 * Author: rlcancian
 *
 * Created on 11 de janeiro de 2022, 22:26
 */

#ifndef TRANSITION_H
#define TRANSITION_H

#include "../../kernel/simulator/ModelDataDefinition.h"
#include "../../kernel/simulator/PluginInformation.h"
#include "../../kernel/util/List.h"
#include "State.h"


class Transition : public ModelDataDefinition  {
public:

	struct TransitionType {
		bool isdefault = false;
		bool nondeterministic = false;
		bool immediatbe = false;
		bool preemptive = false;
		bool history = false;
		bool error = false;
		bool termination = false;
	};
public:

	/*Transition(std::string parameterName, State* originState, State* destinationState, std::string guardExpression = "", TransitionType* transitionType = nullptr) {
		_parameterName = parameterName;
		_originState = originState;
		_destinationState = destinationState;
		_guardExpression = guardExpression;
		if (transitionType == nullptr)
			transitionType = new TransitionType();
		_type = transitionType;
	}*/
	Transition(Model* model, std::string name = "");

	virtual ~Transition() = default;

public: // static
	static ModelDataDefinition* LoadInstance(Model* model, PersistenceRecord *fields);
	static PluginInformation* GetPluginInformation();
	static ModelDataDefinition* NewInstance(Model* model, std::string name = "");
public:
	virtual std::string show();

protected: // must be overriden 
	virtual bool _loadInstance(PersistenceRecord *fields);
	virtual void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);
protected: // could be overriden 
	virtual bool _check(std::string* errorMessage);
	virtual ParserChangesInformation* _getParserChangesInformation();
private:

	const struct DEFAULT_VALUES {
		const double totalArea = 1;
		const unsigned int capacity = 10;
		const double unitsPerArea = 1;
	} DEFAULT;
	double _totalArea = DEFAULT.totalArea;
	unsigned int _capacity = DEFAULT.capacity;
	double _unitsPerArea = DEFAULT.unitsPerArea;

private:
	std::string _parameterName;
	std::string _guardExpression;
	State* _originState;
	State* _destinationState;
	TransitionType* _type;
	List<std::string*>* _outputActions = new List<std::string*>();
	List<std::string*>* _setActions = new List<std::string*>();
};

#endif /* TRANSITION_H */
