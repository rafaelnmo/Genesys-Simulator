#include "Smart_EFSM2.h"

// you have to included need libs

// GEnSyS Simulator
#include "../../../../kernel/simulator/Simulator.h"

// Model Components
#include "../../../../plugins/components/Create.h"
#include "../../../../plugins/components/Dispose.h"
#include "../../../../plugins/components/Assign.h"
#include "../../../../plugins/data/Variable.h"
#include "../../../../plugins/data/EFSM.h"
#include "../../../../plugins/components/FSM_State.h"
#include "../../../../plugins/components/FSM_Transition.h"
#include "../../../../plugins/components/FSM_State.h"
#include "../../../../plugins/components/FSM_ModalModel.h"
#include "../../../../plugins/components/Delay.h"


#include "../../../TraitsApp.h"

Smart_EFSM2::Smart_EFSM2() {
}

/**
 * This is the main function of the application. 
 * It instanciates the simulator, builds a simulation model and then simulate that model.
 */
int Smart_EFSM2::main(int argc, char** argv) {
	// instantiate simulator
	Simulator* genesys = new Simulator();
	genesys->getTracer()->setTraceLevel(TraitsApp<GenesysApplication_if>::traceLevel);
	setDefaultTraceHandlers(genesys->getTracer());
    PluginManager* plugins = genesys->getPlugins();
    plugins->autoInsertPlugins("autoloadplugins.txt");
	// create model
	Model* model = genesys->getModels()->newModel();
    
    EntityType* entityType = new EntityType(model, "Person");
    Create* create1 = plugins->newInstance<Create>(model);
	create1->setDescription("Traffic light");
    create1->setEntityType(entityType);
    create1->setTimeBetweenCreationsExpression("1");
    create1->setTimeUnit(Util::TimeUnit::minute);

    Assign* assign1 = new Assign(model);
    assign1->setDescription("Arrive in traffic light");
    Assignment* assigment1 = new Assignment("pedestrian", "1");
    assign1->getAssignments()->insert(assigment1);
    create1->getConnections()->insert(assign1);

	Delay* delay1 = plugins->newInstance<Delay>(model); // the default delay time is 1.0 s
    delay1->setDescription("Browse");
    delay1->setDelayExpression("10");
    delay1->setDelayTimeUnit(Util::TimeUnit::second);
    assign1->getConnections()->insert(delay1);

	Variable* varCount = plugins->newInstance<Variable>(model, "countWait");
	varCount->setInitialValue(0.0, "countWait"); 

	Variable* varSigR = plugins->newInstance<Variable>(model, "sigR");
	varSigR->setInitialValue(1.0, "sigR"); 

    Variable* varSigG = plugins->newInstance<Variable>(model, "sigG");
	varSigG->setInitialValue(0.0, "sigG"); 

    Variable* varSigY = plugins->newInstance<Variable>(model, "sigY");
	varSigY->setInitialValue(0.0, "sigY"); 
    
    ExtendedFSM* efsm2 = plugins->newInstance<ExtendedFSM>(model, "efsm_1");
    efsm2->insertVariable(varCount);
    efsm2->insertVariable(varSigR);
    efsm2->insertVariable(varSigG);
    efsm2->insertVariable(varSigY);


    FSM_State* stateRed = plugins->newInstance<FSM_State>(model, "red");
    stateRed->setEFSM(efsm2);
    stateRed->setAsInitialState();

    FSM_State* stateGreen = plugins->newInstance<FSM_State>(model, "green");
    stateGreen->setEFSM(efsm2);
    stateGreen->setAsInitialState();

    FSM_State* stateYellow = plugins->newInstance<FSM_State>(model, "yellow");
    stateYellow->setEFSM(efsm2);
    stateYellow->setAsInitialState();

    FSM_State* statePending = plugins->newInstance<FSM_State>(model, "pending");
    statePending->setEFSM(efsm2);
    statePending->setAsInitialState();

    FSM_Transition* transition1 = plugins->newInstance<FSM_Transition>(model, "transition_1");
    transition1->setGuardExpression(""); // 
    transition1->setOutputActions("sigR = 1");
    transition1->setSetActions("countWait = countWait + 1");
    stateRed->getConnections()->insert(transition1);
    transition1->getConnections()->insert(stateRed);


    FSM_Transition* transition2 = plugins->newInstance<FSM_Transition>(model,"transition_2");
    transition2->setGuardExpression("countWait >= 60"); // countWait >= 60
    transition2->setOutputActions("sigG = 1 and sigR = 0");
    transition2->setSetActions("countWait = 0");
    stateRed->getConnections()->insert(transition2);
    transition2->getConnections()->insert(stateGreen);

    //test
    FSM_Transition* transition3 = plugins->newInstance<FSM_Transition>(model,"transition_3");
    transition3->setGuardExpression("countWait < 60"); // cout < 60
    transition3->setOutputActions("sigG = 1");
    transition3->setSetActions("countWait = countWait + 1");
    stateGreen->getConnections()->insert(transition3);
    transition3->getConnections()->insert(stateGreen);

    FSM_Transition* transition9 = plugins->newInstance<FSM_Transition>(model,"transition_9");
    transition9->setGuardExpression("(pedestrian == 1) and (countWait >= 60)"); //pedestrian = 1 and countWait >= 60
    transition9->setOutputActions("sigY = 1 and sigG = 0");
    transition9->setSetActions("countWait = 0");
    stateGreen->getConnections()->insert(transition9);
    transition9->getConnections()->insert(stateYellow);

    FSM_Transition* transition4 = plugins->newInstance<FSM_Transition>(model,"transition_4");
    transition4->setGuardExpression("(pedestrian == 1) and (countWait < 60)"); //pedestrian and countWait < 60
    transition4->setOutputActions("sigG = 1");
    transition4->setSetActions("countWait = countWait + 1");
    stateGreen->getConnections()->insert(transition4);
    transition4->getConnections()->insert(statePending);

    FSM_Transition* transition5 = plugins->newInstance<FSM_Transition>(model, "transition_5");
    transition5->setGuardExpression(""); //
    transition5->setOutputActions("");
    transition5->setSetActions("countWait = countWait + 1");
    statePending->getConnections()->insert(transition5);
    transition5->getConnections()->insert(statePending);

    FSM_Transition* transition6 = plugins->newInstance<FSM_Transition>(model, "transition_6");
    transition6->setGuardExpression("countWait >= 60"); // countWait >= 60
    transition6->setOutputActions("sigY = 1 and sigG = 0");
    transition6->setSetActions("countWait = 0");
    statePending->getConnections()->insert(transition6);
    transition6->getConnections()->insert(stateYellow);


    FSM_Transition* transition7 = plugins->newInstance<FSM_Transition>(model, "transition_7");
    transition7->setGuardExpression(""); //
    transition7->setOutputActions("");
    transition7->setSetActions("countWait = countWait + 1");
    stateYellow->getConnections()->insert(transition7);
    transition7->getConnections()->insert(stateYellow);

    FSM_Transition* transition8 = plugins->newInstance<FSM_Transition>(model, "transition_8");
    transition8->setGuardExpression("countWait >= 5"); //countWait >= 5
    transition8->setOutputActions("sigR = 1 and sigY = 0");
    transition8->setSetActions("countWait = 0");
    stateYellow->getConnections()->insert(transition8);
    transition8->getConnections()->insert(stateRed);


    FSM_Transition* transition10 = plugins->newInstance<FSM_Transition>(model,"transition_10");
    transition10->setGuardExpression("");
    transition10->setOutputActions("");
    transition10->setSetActions("");
    transition10->setDefault(true);
    stateRed->getConnections()->insert(transition10);
    transition10->getConnections()->insert(stateRed);

    FSM_ModalModel* modalmodel1 = plugins->newInstance<FSM_ModalModel>(model, "modalmodel_1");
    modalmodel1->setEFSMData(efsm2);
    delay1->getConnections()->insert(modalmodel1);

    Dispose* dispose1 = plugins->newInstance<Dispose>(model);
    dispose1->setReportStatistics(true);
    modalmodel1->getConnections()->insert(dispose1);

	// set options, save and simulate

	model->getSimulation()->setNumberOfReplications(3);
	model->getSimulation()->setReplicationLength(3, Util::TimeUnit::minute);
	model->getSimulation()->setTerminatingCondition("");
	model->getSimulation()->setReplicationReportBaseTimeUnit(Util::TimeUnit::hour);
    model->save("./models/Smart_EFSM2.gen");
	model->getSimulation()->start();	
	// free memory
	delete genesys;
	
	return 0;
};
