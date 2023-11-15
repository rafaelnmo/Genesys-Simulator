#include "State.h"


void FSM_State::_saveInstance(PersistenceRecord *fields, bool saveDefaultValues) {
	fields->saveField("name", _name, "");
}

bool FSM_State::_loadInstance(PersistenceRecord *fields) {
    bool res = true;
    try {
        _name = fields->loadField("name", "");
        //_isInitialState = fields->loadField("isInitialState", );
	} catch (...) {
		res = false;
    }

    return res;
}

std::string FSM_State::show(){}
