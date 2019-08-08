package src.churn.nochurn;
import src.churn.churnbase.ChurnBase;

//
// TODO auto-generated module
//
simple NoChurn extends ChurnBase
{
    parameters:
        @class(NoChurn);
        int num_init_stages;
        int start_spawning;
        double mean_spawn_delay;
        int target_node_count;
}
