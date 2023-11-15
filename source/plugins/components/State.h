#ifndef STATE_H
#define STATE_H

#include "../../kernel/simulator/ModelComponent.h"
#include <string>

class FSM_State : public ModelComponent {
public:

	FSM_State(std::string name, bool isFinalState = false, bool isInitialState = false):
		_name(name),
		// _refinementName(refinementName),
		_isInitialState(isInitialState),
		_isFinalState(isFinalState)
	{}
	virtual ~FSM_State() = default;


    //bool _loadInstance(PersistenceRecord *fields);
    //void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);

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

public: // virtual
	virtual std::string show();
protected: /// virtual protected method that must be overriden
	virtual bool _loadInstance(PersistenceRecord *fields);
	virtual void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);
	/// new virtual methods for all ModelComponents
	virtual void _onDispatchEvent(Entity* entity, unsigned int inputPortNumber) = 0; ///< This method is only for ModelComponents, not ModelDataElements

private:
	std::string _name;
	bool _isInitialState = false;
	bool _isFinalState = false;
	// std::string _refinementName;
};
#endif /* STATE_H */
