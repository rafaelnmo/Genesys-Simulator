#ifndef FSM_STATE_H
#define FSM_STATE_H

#include "../../kernel/simulator/ModelComponent.h"
#include <string>

class FSM_State : public ModelComponent {
public:

	/*FSM_State(std::string name, bool isFinalState = false, bool isInitialState = false):
		_name(name),
		// _refinementName(refinementName),
		_isInitialState(isInitialState),
		_isFinalState(isFinalState)
	{}*/
	FSM_State(Model* model, std::string name = "");
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

	void insertEFSM(ExtendedFSM* efsm){
		_efsm = efsm;
	}

	// void setRefinementName(std::string refinementName) {
	// 	_refinementName = refinementName;
	// }

	// std::string getRefinementName() const {
	// 	return _refinementName;
	// }
public: // static
	static PluginInformation* GetPluginInformation();
	static ModelComponent* LoadInstance(Model* model, PersistenceRecord *fields);
	static ModelDataDefinition* NewInstance(Model* model, std::string name = "");

public: // virtual
	virtual std::string show();
protected: /// virtual protected method that must be overriden
	virtual bool _loadInstance(PersistenceRecord *fields);
	virtual void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);
	/// new virtual methods for all ModelComponents
	virtual void _onDispatchEvent(Entity* entity, unsigned int inputPortNumber); ///< This method is only for ModelComponents, not ModelDataElements

private:
	std::string _name;
    ExtendedFSM* _efsm;
	bool _isInitialState = false;
	bool _isFinalState = false;
	// std::string _refinementName;
};
#endif /* FSM_STATE_H */
