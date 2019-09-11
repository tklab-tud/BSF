import networkx as nx
import os
import re


#def init_graph(SOURCE_FILE, FILE_RESET=False):
#    if os.path.isfile(SOURCE_FILE):
#        print "File is read."
#        G = nx.read_dot(SOURCE_FILE)
#    else:
#        print "Error! The specified source file does not exist."
#        quit()
#    print "Your Graph contains " + str(len(G.nodes())) + " nodes and " + str(len(G.edges())) + " edges."
#    return G


def init_graph(SOURCE_FILE, FILE_RESET=False):
    if os.path.isfile(SOURCE_FILE):
        print("File is read.")
        exp = re.compile(r'\"(\d+)\"->{(.*)}')
        G = nx.DiGraph()
        f = open(SOURCE_FILE, 'r')
        for line in f:
            res = exp.match(line)
            if res:
                n = res.group(1)
                neighbors = res.group(2).replace('\"', "").split(" ")
                for neighbor in neighbors:
                    if neighbor != '':
                        G.add_edge(int(n), int(neighbor))
        f.close()
    else:
        print("Error! The specified source file does not exist.")
        quit()
    print("Your Graph contains " + str(len(G.nodes())) + " nodes and " + str(len(G.edges())) + " edges.")
    return G


def init_multidigraph(SOURCE_FILE, FILE_RESET=False):
    if os.path.isfile(SOURCE_FILE):
        print("File is read.")
        exp = re.compile(r'\"(\d+)\"->{(.*)}')
        G = nx.MultiDiGraph()
        f = open(SOURCE_FILE, 'r')
        for line in f:
            res = exp.match(line)
            if res:
                n = res.group(1)
                neighbors = res.group(2).replace('\"', "").split(" ")
                for neighbor in neighbors:
                    if neighbor != '':
                        G.add_edge(int(n), int(neighbor))
        f.close()
    else:
        print("Error! The specified source file does not exist.")
        quit()
    print("Your Graph contains " + str(len(G.nodes())) + " nodes and " + str(len(G.edges())) + " edges.")
    return G


def init_graph_clean(SOURCE_FILE, FILE_RESET=False, Verbose = False):
    if os.path.isfile(SOURCE_FILE):
        if Verbose:
            print("File is read.")
        exp = re.compile(r'\"(\d+)\"->{(.*)}')
        G = nx.DiGraph()
        f = open(SOURCE_FILE, 'r')
        for line in f:
            res = exp.match(line)
            if res:
                n = res.group(1)
                neighbors = res.group(2).replace('\"', "").split(" ")
                for neighbor in neighbors:
                    if not neighbor == '':
                        G.add_edge(int(n), int(neighbor))
        f.close()
    else:
        print("Error! The specified source file does not exist.")
        quit()
    if Verbose:
        print("Your Graph contains " + str(len(G.nodes())) + " nodes and " + str(len(G.edges())) + " edges.")

    for node in G.nodes():
        if G.out_degree(node) == 0:
            G.remove_node(node)
    return G
