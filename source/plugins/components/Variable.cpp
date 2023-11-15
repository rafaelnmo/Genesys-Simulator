#include "Variable.h"

void FSM_Variable::_saveInstance(PersistenceRecord *fields, bool saveDefaultValues) {
	fields->saveField("name", _name, "");
}

bool FSM_Variable::_loadInstance(PersistenceRecord *fields) {
    bool res = true;
    try {
        _name = fields->loadField("name", "");
	} catch (...) {
		res = false;
    }

    return res;
}

std::string FSM_Variable::show(){}
