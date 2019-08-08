package src.churn.lifetimechurn;
import src.churn.churnbase.ChurnBase;

//
// TODO auto-generated module
//
simple LifetimeChurn extends ChurnBase
{
    parameters:
        @class(LifetimeChurn);
        int num_init_stages;
        int start_spawning;
        double mean_spawn_delay;
        int target_node_count;

        double shape_arrival = default(0.66);
        double shape_lifetime = default(0.28);
        double scale_lifetime = default(1193.317);
}
