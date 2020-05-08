package src.networks.basicnetwork;
import src.routers.basicrouter.BasicRouter;
import src.churn.churnbase.ChurnBase;
import src.globalnodelist.GlobalNodeList;
import src.statistics.NetworkAnalyzer;
import src.churninitializer.ChurnInitializer;
import src.botmaster.Botmaster;

network BasicNetwork
{
    parameters:
        @isNetwork;
    submodules:
        BasicRouter: BasicRouter;
        GlobalNodeList: GlobalNodeList;
        NetworkAnalyzer: NetworkAnalyzer;
        ChurnGenerator[0]: ChurnBase;
        ChurnInitializer: ChurnInitializer;
        Botmaster: Botmaster;
}
