package src.nodes.simplecrawler;

import src.nodes.simplebot.SimpleBot;
//
// TODO auto-generated module
//
simple SimpleCrawler extends SimpleBot
{
     @class(SimpleCrawler);
     int request_per_crawl;
     double crawler_start_time @unit(s);
     double crawl_timeout @unit(s);
}