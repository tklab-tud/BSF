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
}
