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

	Transition(std::string parameterName, FSM_State* originState, FSM_State* destinationState, std::string guardExpression = "", TransitionType* transitionType = nullptr) {
		_parameterName = parameterName;
		_originState = originState;
		_destinationState = destinationState;
		_guardExpression = guardExpression;
		if (transitionType == nullptr)
			transitionType = new TransitionType();
		_type = transitionType;
	}
	
	virtual ~Transition() = default;

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
