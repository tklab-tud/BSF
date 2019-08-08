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
    gates:
        input net_in;
        output net_out;
}
