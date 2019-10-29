package src.nodes.nodebase;

//
// TODO auto-generated module
//
simple NodeBase
{
    string configname;
    int run_number;
    int total_nodes;
    double snapshotInterval @unit(s) = default(1800s);
    double latency_mean @unit(s) = default(0ms);
    double latency_stddev @unit(s) = default(0ms);
    gates:
        input net_in;
        output net_out;
}
