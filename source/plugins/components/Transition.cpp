#include "Transition.h"


void FSM_Transition::_saveInstance(PersistenceRecord *fields, bool saveDefaultValues) {
    //fields->saveField("name", _name, "");
}

bool FSM_Transition::_loadInstance(PersistenceRecord *fields) {
    bool res = true;
    try {
	} catch (...) {
		res = false;
    }
}

std::string FSM_Transition::show(){}
