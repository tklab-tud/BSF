package src.nodes.simplebot;
import src.nodes.nodebase.NodeBase;

simple SimpleBot extends NodeBase
{
    parameters:
        @class(SimpleBot);
        @signal[Neighbor];
        int mmInterval;
        int max_nl_size;
        int nl_min_threshold;
        int bootstrap_nodes;
        int nl_return_size;
        double delay @unit(s) = default(0ms);
        int max_parallel_conns = default(65534);
}
