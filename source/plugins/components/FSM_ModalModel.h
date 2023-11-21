#ifndef FSM_MODALMODEL_H
#define FSM_MODALMODEL_H

#include "../../kernel/simulator/ModelComponent.h"
#include <string>
#include "../data/EFSM.h"

class FSM_ModalModel : public ModelComponent {
public:

	/*FSM_ModalModel(std::string name, bool isFinalState = false, bool isInitialState = false):
		_name(name),
		// _refinementName(refinementName),
		_isInitialState(isInitialState),
		_isFinalState(isFinalState)
	{}*/
	FSM_ModalModel(Model* model, std::string name = "");
	virtual ~FSM_ModalModel() = default;


    //bool _loadInstance(PersistenceRecord *fields);
    //void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);

	void setName(std::string name) {
		_name = name;
	}

	std::string getName() const {
		return _name;
	}

	void setEFSM(EFSM* efsm) {
		_efsm = efsm;
	}

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
	EFSM* _efsm;
};
#endif /* FSM_MODALMODEL_H */
