#ifndef TRANSITION_H
#define TRANSITION_H

#include "../../kernel/simulator/ModelComponent.h"
#include <string>


class FSM_Transition : public ModelComponent {
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

	FSM_Transition(std::string guardExpression, std::string originState, std::string destinationState, std::string outputActions, std::string setActions):
		_guardExpression(guardExpression),
		_originState(originState),
		_destinationState(destinationState),
		_outputActions(outputActions),
		_setActions(setActions)
	{}
		// if (transitionType == nullptr)
		// 	transitionType = new TransitionType();
		// _type = transitionType;

    //bool _loadInstance(PersistenceRecord *fields);
    //void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);

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

public: // virtual
	virtual std::string show();
protected: /// virtual protected method that must be overriden
	virtual bool _loadInstance(PersistenceRecord *fields);
	virtual void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);
	/// new virtual methods for all ModelComponents
	virtual void _onDispatchEvent(Entity* entity, unsigned int inputPortNumber) = 0; ///< This method is only for ModelComponents, not ModelDataElements

private:
	std::string _guardExpression;
	std::string _originState;
	std::string _destinationState;
	std::string _outputActions;
	std::string _setActions;
};


#endif /* TRANSITION_H */
