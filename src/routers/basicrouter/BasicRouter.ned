package src.routers.basicrouter;

//
// TODO auto-generated module
//
simple BasicRouter
{
    parameters:
        int total_nodes = default(10);
        bool record_trace = default(false);
        double start_recording_trace @unit(s) = default(0d);
        int run_number;
    gates:
        input nodes_in[total_nodes] @loose;
        output nodes_out[total_nodes] @loose;
}
