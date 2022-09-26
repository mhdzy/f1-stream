#!/usr/bin/python
"""
For testing rapid updates of ScatterPlotItem under various conditions.
"""

import argparse
import numpy as np
import pandas as pd
import sys
from time import perf_counter

import pyqtgraph as pg
import pyqtgraph.parametertree as ptree
from pyqtgraph.Qt import QtCore, QtWidgets

parser = argparse.ArgumentParser(description="Real-time track telemetry data display.")
parser.add_argument("--track", type=str, nargs="+", default="spa", help="Track name to render.")
args = parser.parse_args()

TRACK = args.track[0]

translate = QtCore.QCoreApplication.translate

app = pg.mkQApp()
param = ptree.Parameter.create(
    name=translate("ScatterPlot", "Parameters"),
    type="group",
    children=[
        dict(
            name="paused",
            title=translate("ScatterPlot", "Paused:    "),
            type="bool",
            value=False,
        ),
        dict(
            name="count",
            title=translate("ScatterPlot", "Count:    "),
            type="int",
            limits=[1, None],
            value=10,
            step=0,
        ),
        dict(
            name="size",
            title=translate("ScatterPlot", "Size:    "),
            type="int",
            limits=[1, None],
            value=10,
        ),
        dict(
            name="randomize",
            title=translate("ScatterPlot", "Randomize:    "),
            type="bool",
            value=False,
        ),
        dict(name="pxMode", title="pxMode:    ", type="bool", value=True),
        dict(name="useCache", title="useCache:    ", type="bool", value=True),
        dict(
            name="mode",
            title=translate("ScatterPlot", "Mode:    "),
            type="list",
            limits={
                translate("ScatterPlot", "New Item"): "newItem",
                translate("ScatterPlot", "Reuse Item"): "reuseItem",
                translate("ScatterPlot", "Simulate Pan/Zoom"): "panZoom",
                translate("ScatterPlot", "Simulate Hover"): "hover",
            },
            value="reuseItem",
        ),
    ],
)

for c in param.children():
    c.setDefault(c.value())

pt = ptree.ParameterTree(showHeader=False)
pt.setParameters(param)
p = pg.PlotWidget()
splitter = QtWidgets.QSplitter()
splitter.addWidget(pt)
splitter.addWidget(p)
splitter.show()

READ_PARTICIPANTS = 0


def refreshParticipants():
    global READ_PARTICIPANTS
    try:
        dplayers = pd.read_csv("data/" + TRACK + "/parsed/Participants.csv")
        my_ids = dplayers[dplayers.m_name == "Sumosusa"]["m_carID"].unique()
        one_id = my_ids.item(0)
        READ_PARTICIPANTS = 1
    except:
        one_id = -1
    return one_id


one_id = -1


def refresh():
    print("refresh" + str(ptr))
    global one_id, dat
    if READ_PARTICIPANTS == 0:
        one_id = refreshParticipants()
    try:
        motion = pd.read_csv("data/" + TRACK + "/parsed/MotionHack.csv")
        speed = pd.read_csv("data/" + TRACK + "/parsed/TelemetryHack.csv")
    except:
        motion = pd.DataFrame({"frame": [0], "x": [0], "y": [0]})
        speed = pd.DataFrame({"frame": [0], "speed": [0]})
    dat = pd.merge(motion, speed, on="frame", how="left")


def refreshRange():
    global p
    p.setRange(
        xRange=[min(dat.x), max(dat.x)],
        yRange=[min(dat.y), max(dat.y)],
    )


dat = pd.DataFrame()
data = {}
item = pg.ScatterPlotItem()
hoverBrush = pg.mkBrush("y")
ptr = 0
lastTime = perf_counter()
fps = None
timer = QtCore.QTimer()
refresh()
import pdb


def refreshData():
    global data
    # list of all pixel thingies

    clean_speed = [x for x in [x if not np.isnan(x) else 0 for x in dat["speed"]]]
    divisor = max(clean_speed) if max(clean_speed) > 0 else 1
    norm_speed = [x / divisor for x in clean_speed]
    brushes = [pg.mkBrush([256 * x, 256 - (256 * x), 256]) for x in norm_speed]

    data = {
        "pos": np.random.normal(size=(2, len(dat)), scale=100),
        "pen": [pg.mkPen(256) for x in [0]],
        "brush": brushes,
        "size": (np.array([0.2] * len(dat)) * param["size"]).astype(int),
    }


def mkDataAndItem():
    # pdb.set_trace(header = "mkDataAndItem")
    global data, fps
    refresh()
    refreshRange()
    refreshData()
    data["pen"][0] = pg.mkPen("w")
    data["size"][0] = param["size"]
    data["brush"][0] = pg.mkBrush("g")
    mkItem()


def mkItem():
    # pdb.set_trace(header = "mkItem")
    global item
    item = pg.ScatterPlotItem(pxMode=param["pxMode"], **getData())
    item.opts["useCache"] = param["useCache"]
    p.clear()
    refreshRange()
    p.addItem(item)


import array


def getData():
    global dat, data
    refresh()
    refreshRange()
    refreshData()
    pos = data["pos"]
    pen = data["pen"]
    size = data["size"]
    brush = data["brush"]
    if not param["randomize"]:
        pen = pen[0]
        size = size[0]
        brush = brush[0]
    return dict(
        x=np.array([x for x in dat.x]),
        y=np.array([x for x in dat.y]),
        pen=pen,
        brush=brush,
        size=size,
    )


def update():
    global ptr, lastTime, fps
    mode = param["mode"]
    if mode == "newItem":
        mkItem()
    elif mode == "reuseItem":
        item.setData(**getData())
    elif mode == "panZoom":
        item.viewTransformChanged()
        item.update()
    elif mode == "hover":
        pts = item.points()
        old = pts[(ptr - 1) % len(pts)]
        new = pts[ptr % len(pts)]
        item.pointsAt(new.pos())
        old.resetBrush()  # reset old's brush before setting new's to better simulate hovering
        new.setBrush(hoverBrush)
    ptr += 1
    now = perf_counter()
    dt = now - lastTime
    lastTime = now
    if fps is None:
        fps = 1.0 / dt
    else:
        s = np.clip(dt * 3.0, 0, 1)
        fps = fps * (1 - s) + (1.0 / dt) * s
    p.setTitle("%0.2f fps" % fps)
    p.repaint()
    # app.processEvents()  # force complete redraw for every plot


mkDataAndItem()

for name in ["count", "size"]:
    param.child(name).sigValueChanged.connect(mkDataAndItem)

for name in ["useCache", "pxMode", "randomize"]:
    param.child(name).sigValueChanged.connect(mkItem)

param.child("paused").sigValueChanged.connect(
    lambda _, v: timer.stop() if v else timer.start()
)
timer.timeout.connect(update)
timer.start(500)

if __name__ == "__main__":
    pg.exec()
