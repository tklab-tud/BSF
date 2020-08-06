# -*- coding: utf-8 -*-
import dash
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input, Output
import os
import plotly.graph_objs as go
from natsort import natsorted as ns

import networkx as nx

import GraphUtil as GraphUtil

folder = '../simulations/dumps'
g_folder = 'graphs'
c_folder = 'crawlers'
s_folder = 'sensors'
graph_files = []
crawler_files = []
sensor_files = []
fig_to_dir = {}
crawler_to_dir = {}
labels = []


def create_traces(graph):
    pos = nx.spring_layout(graph)

    # Create edges
    print("Load Edges")
    edge_x = []
    edge_y = []
    for edge in graph.edges():
        x0, y0 = pos[edge[0]]
        x1, y1 = pos[edge[1]]
        edge_x.append(x0)
        edge_x.append(x1)
        edge_x.append(None)
        edge_y.append(y0)
        edge_y.append(y1)
        edge_y.append(None)

    edge_trace = go.Scattergl(
        x=edge_x, y=edge_y,
        line=dict(width=0.5, color='#888'),
        hoverinfo='none',
        mode='lines')

    print("Load Node Traces")
    node_trace = go.Scattergl(
        x=[],
        y=[],
        text=[],
        mode='markers',
        hoverinfo='text',
        marker=dict(
            showscale=False,
            colorscale='YlGnBu',
            reversescale=True,
            color=[],
            size=15,
            colorbar=dict(
                thickness=15,
                title='Node Connections',
                xanchor='left',
                titleside='right'
            ),
            line=dict(width=0)))

    print("Load Nodes")
    for node in graph.nodes():
        x, y = pos[node]  # ['pos']
        node_trace['x'] += tuple([x])
        node_trace['y'] += tuple([y])
        node_trace['text'] += tuple([node])
    colors = ['black'] * len(pos)

    node_trace['marker'].update({'color': colors})

    return edge_trace, node_trace, pos


def crawler_id(name):
    return name[name.rfind("Crawler") + len("Crawler"):name.rfind(".")]


def snapshot_time(name):
    return name[name.find("Time")+len("Time"):name.rfind("Nodes")]


# MAIN
for root, dirs, files in os.walk(folder):
    if g_folder in dirs:
        labels.append({'label': root[root.rfind("/")+1:], 'value': root})

    for file in files:
        file = root + '/' + file
        if g_folder in root:
            graph_files.append(file)
        elif c_folder in root:
            crawler_files.append(file)
        elif s_folder in root:
            sensor_files.append(file)

    figures = {}
    for file in ns(graph_files):
        # Create graph
        print("Load graphviz file: ", file)
        nx_graph = GraphUtil.init_multidigraph(file)

        edge_trace, node_trace, positions = create_traces(nx_graph)
        figure = [edge_trace, node_trace]
        timestamp = snapshot_time(file)
        figures.update({timestamp: figure})

        fig_to_dir.update({root[:-len(g_folder)-1]: figures})

    print("Load Crawler files")
    crawler_ids = []
    for file in ns(crawler_files):
        crawler_ids.append(crawler_id(file))
    crawler_ids = set(crawler_ids)

    crawler = {}
    for id in crawler_ids:
        snapshot = {}
        for file in ns(crawler_files):
            if id == crawler_id(file):
                crawler_nodes = []
                timestamp = snapshot_time(file)
                i = 0
                for line in open(file):
                    entry = line.split(';')
                    if len(entry) > 1:               
                        crawler_nodes.append(i)
                    i += 1
                snapshot.update({int(timestamp): crawler_nodes})
        #snapshot = dict(sorted(snapshot.items()))
        crawler.update({id: snapshot})

    if crawler:
        crawler_to_dir.update({root[:-len(c_folder)-1]: crawler})

    graph_files = []
    crawler_files = []
    sensor_files = []

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']

app = dash.Dash(__name__, external_stylesheets=external_stylesheets)

app.layout = html.Div(children=[
    html.H1(children='Botnet Visualization'),

    html.Div([
        dcc.Graph(id='Graph'),
        # Slider
        dcc.Slider(
            id='snapshot--slider',
            min=1,
            max=len(figures),
            value=len(figures),
            marks={str(id): str(id) for id in range(0, len(figures))},
            step=1
        ),
    ], style={'width': '79%', 'display': 'inline-block', 'float': 'left'}),

    html.Div([
        dcc.Dropdown(
            id='folder--dropdown',
            options=labels,
            value=labels[0]['value']
        ),
        dcc.Checklist(
            id='options--checklist',
            options=[
                {'label': 'Crawler', 'value': 'crawler'},
                {'label': 'Sensor', 'value': 'sensor'},
                {'label': 'Offline Bots', 'value': 'offline'}
            ],
            value=[]
        )
    ], style={'width': '19%', 'display': 'inline-block'})
])


@app.callback(
    Output('Graph', 'figure'),
    [Input('snapshot--slider', 'value'),
     Input('options--checklist', 'value'),
     Input('folder--dropdown', 'value')])
def update_graph(snapshot_value, options, dir_param):
    figures = []
    if dir_param:
        print("GRAPH", dir_param)
        for fig in fig_to_dir[dir_param].values():
            figures.append(fig)
    if snapshot_value > len(figures):
        snapshot_value = len(figures)
    figure = figures[snapshot_value-1]
    if isinstance(options, list):
        if 'crawler' in options:
            # currently it only supports one crawler
            node_trace = figure[1]
            colors = node_trace['marker']['color']
            color_l = list(colors)

            ids = node_trace['text']
            id_dict = {}
            pos = 0
            for id in ids:
                id_dict[id] = pos
                pos += 1
            for crawler in crawler_to_dir[dir_param].values():
                if snapshot_value > len(crawler.values()):
                    crawled_nodes = list(crawler.values())[snapshot_value-1-len(crawler.values())]
                else: 
                    crawled_nodes = []    
                print("crawled nodes:", crawled_nodes)
                for node in crawled_nodes:
                    if str(node) in id_dict.keys():
                        color_l[id_dict[str(node)]] = 'green'
            colors = tuple(color_l)
            node_trace['marker'].update({'color': colors})
            figure[1] = node_trace
        else:
            node_trace = figure[1]
            colors = node_trace['marker']['color']
            colors = ['black'] * len(colors)
            node_trace['marker'].update({'color': colors})
            figure[1] = node_trace

    return {
        'data': figure,
        'layout': go.Layout(
            titlefont=dict(size=16),
            showlegend=False,
            hovermode='closest',
            margin=dict(b=20, l=5, r=5, t=40),
            height=800,
            xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
            yaxis=dict(showgrid=False, zeroline=False, showticklabels=False))
    }


@app.callback(
    [Output('snapshot--slider', 'min'),
     Output('snapshot--slider', 'max'),
     Output('snapshot--slider', 'value'),
     Output('snapshot--slider', 'marks')],
    [Input('folder--dropdown', 'value')])
def read_files(dir_param):
    figures = fig_to_dir[dir_param]
    return [1, len(figures), len(figures), {str(id): str(id) for id in range(0, len(figures))}]


if __name__ == '__main__':
    app.run_server(debug=True)
