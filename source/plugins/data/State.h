/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/*
 * File:   State.h
 * Author: rlcancian
 *
 * Created on 11 de janeiro de 2022, 22:26
 */

#ifndef STATE_H
#define STATE_H

#include "../../kernel/simulator/ModelDataDefinition.h"
#include "../../kernel/simulator/PluginInformation.h"

class State : public ModelDataDefinition {
public: /// constructors
	State(Model* model, std::string name = "");
	virtual ~State() = default;

public: // static
	static ModelDataDefinition* LoadInstance(Model* model, PersistenceRecord *fields);
	static PluginInformation* GetPluginInformation();
	static ModelDataDefinition* NewInstance(Model* model, std::string name = "");
public:
	virtual std::string show();
void setName(std::string _name) {
		this->_name = _name;
	}

	std::string getName() const {
		return _name;
	}

	void setIsFinalState(bool _isFinalState) {
		this->_isFinalState = _isFinalState;
	}

	bool isFinalState() const {
		return _isFinalState;
	}

	void setIsInitialState(bool _isInitialState) {
		this->_isInitialState = _isInitialState;
	}

	bool isInitialState() const {
		return _isInitialState;
	}

	void setRefinementName(std::string _refinementName) {
		this->_refinementName = _refinementName;
	}

	std::string getRefinementName() const {
		return _refinementName;
	}

protected: // must be overriden 
	virtual bool _loadInstance(PersistenceRecord *fields);
	virtual void _saveInstance(PersistenceRecord *fields, bool saveDefaultValues);
protected: // could be overriden 
	virtual bool _check(std::string* errorMessage);
	virtual ParserChangesInformation* _getParserChangesInformation();
private:

	const struct DEFAULT_VALUES {
		const double totalArea = 1;
		const unsigned int capacity = 10;
		const double unitsPerArea = 1;
	} DEFAULT;
	double _totalArea = DEFAULT.totalArea;
	unsigned int _capacity = DEFAULT.capacity;
	double _unitsPerArea = DEFAULT.unitsPerArea;
	
	private:
	std::string _name;
	std::string _refinementName;
	bool _isInitialState;
	bool _isFinalState;

private:
	//@TODO: Add statisticCollector for ProportionOfStorageUsage
};

#endif /* STATE_H */

