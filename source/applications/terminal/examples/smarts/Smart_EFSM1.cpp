#include "Smart_EFSM1.h"
#include <map>

// you have to included need libs

// GEnSyS Simulator
#include "../../../../kernel/simulator/Simulator.h"

// Model Components
#include "../../../../plugins/components/Create.h"
#include "../../../../plugins/components/Dispose.h"
#include "../../../../plugins/data/EFSM.h"
#include "../../../../plugins/components/FiniteStateMachine.h"
#include "../../../TraitsApp.h"


Smart_EFSM1::Smart_EFSM1() {
}

/**
 * This is the main function of the application. 
 * It instanciates the simulator, builds a simulation model and then simulate that model.
 */
int Smart_EFSM1::main(int argc, char** argv) {
	// instantiate simulator
	Simulator* genesys = new Simulator();
	genesys->getTracer()->setTraceLevel(TraitsApp<GenesysApplication_if>::traceLevel);
	setDefaultTraceHandlers(genesys->getTracer());
    PluginManager* plugins = genesys->getPlugins();
    plugins->autoInsertPlugins("/mnt/HD_EXTERNO/computerScience/course/14ºFASE/modSim/new/Genesys-Simulator/autoloadplugins.txt");
	// create model
	Model* model = genesys->getModels()->newModel();
    Create* create1 = plugins->newInstance<Create>(model);
	
	// initialize model parts
    FiniteStateMachine* fsm = plugins->newInstance<FiniteStateMachine>(model, "ExtendedFinishMachine_1");
	fsm->setName("fsm_1");
    std::cout << fsm->getName() << "\n";
	std::cout << fsm->show() << "\n";
    
    Dispose* dispose1 = plugins->newInstance<Dispose>(model);
    std::cout << dispose1->getName();
    std::cout << dispose1->getId();

	// connect model components to create a "workflow"
	create1->getConnections()->insert(fsm);
	fsm->getConnections()->insert(dispose1);

    dispose1->setReportStatistics(true);
	
    std::cout << "\nplugins: " << plugins->front() << "\n";

	// creating states of efsm
    fsm->_createInternalAndAttachedData();

    fsm->_internalDataDefinition->insertState("Counting", false, true);
    std::cout <<  "state Name: " << fsm->_internalDataDefinition->getStates()->at(0).getName() << "\n";
    
    fsm->_internalDataDefinition->insertVariable("c", 0);
    fsm->_internalDataDefinition->insertVariable("M", 100);

    // creating transitions of each state of efsm
    //fsm->_internalDataDefinition->insertTransition("up = 1 & down = 0 & c < M", "Counting", "Counting","carsAmount = c + 1", "c = c + 1");
    fsm->_internalDataDefinition->insertTransition("", "Counting", "Counting","carsAmount = c + 1", "c = c + 1");
    std::cout <<  "Guard Expression: " << fsm->_internalDataDefinition->getTransitions()->at(0).getGuardExpression() << "\n";
    fsm->_internalDataDefinition->insertTransition("down = 1 & up = 0 & c > 0", "Counting", "Counting","carsAmount = c - 1", "c = c - 1");
	
	// run the simulation
    auto outputActions = std::map<std::string,int>{};
    auto input = std::map<std::string,int>{};
    input.insert(std::pair<std::string,int>("up", 1));
    input.insert(std::pair<std::string,int>("down", 0));

    bool isfinalState;
    for (int i = 1; i <= 10; i++){
        isfinalState = fsm->_internalDataDefinition->fire(input, outputActions);
        std::cout << "isfinalState: " << isfinalState <<std::endl;
        std::cout << "outputActions: " << std::endl;
        for(auto outputAction: outputActions){
            std::cout << outputAction.first << " = " << outputAction.second << std::endl;

        }
       
    }

    // set options, save and simulate
	model->getSimulation()->setNumberOfReplications(1);
	model->getSimulation()->setReplicationLength(60, Util::TimeUnit::second);
	//model->getSimulation()->setTerminatingCondition("count(Dispose_1.CountNumberIn)>30");
	model->getSimulation()->setReplicationReportBaseTimeUnit(Util::TimeUnit::hour);
    model->save("./models/Smart_EFSM1.gen");
	model->getSimulation()->start();	
	// free memory
	delete genesys;
	
	return 0;
};
