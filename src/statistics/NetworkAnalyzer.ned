package src.statistics;

//
// TODO auto-generated module
//
simple NetworkAnalyzer
{
    parameters:
        @class(NetworkAnalyzer);
        @display("i=old/ring");
        double snapshotInterval @unit(s) = default(1800s);
        int run_number;
        int total_nodes;
        string configname;
        bool remove_offline = default(true);
}
