package src.churn.staticnochurn;
import src.churn.nochurn.NoChurn;

//
// TODO auto-generated module
//
simple StaticNoChurn extends NoChurn
{
    parameters:
        @class(StaticNoChurn);
        int no_churn_startup @unit(s);
}
