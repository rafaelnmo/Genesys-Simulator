#ifndef FSM_VARIABLE_H
#define FSM_VARIABLE_H

#include "../../kernel/simulator/ModelComponent.h"
#include <string>

class FSM_Variable : public ModelComponent {
public:
	/*FSM_Variable(Model* model, std::string name, int value):
	_name(name),
	_value(value)
	{}*/
	FSM_Variable(Model* model, std::string name = "");
	
	virtual ~FSM_Variable() = default;


    //bool _loadInstance(PersistenceRecord *fields);
    //void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);

	std::string getName(){
		return _name;
	}

	void setInitialValue(int initialValue){
		_value = initialValue;
	}

	int _value;

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
};

#endif /* FSM_VARIABLE_H */
