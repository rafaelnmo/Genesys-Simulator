#ifndef VARIABLE_H
#define VARIABLE_H

#include "../../kernel/simulator/ModelComponent.h"
#include <string>

class FSM_Variable : public ModelComponent {
public:
	FSM_Variable(std::string name, int value):
	_name(name),
	_value(value)
	{}

    //bool _loadInstance(PersistenceRecord *fields);
    //void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);

	std::string getName(){
		return _name;
	}

	int _value;

public: // virtual
	virtual std::string show();
protected: /// virtual protected method that must be overriden
	virtual bool _loadInstance(PersistenceRecord *fields);
	virtual void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);
	/// new virtual methods for all ModelComponents
	virtual void _onDispatchEvent(Entity* entity, unsigned int inputPortNumber) = 0; ///< This method is only for ModelComponents, not ModelDataElements


private:
	std::string _name;
};

#endif /* VARIABLE_H */
