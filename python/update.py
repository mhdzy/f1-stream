#!/bin

import os
import pandas as pd
import re
import shutil

filenames = os.listdir("data/spain/raw/")
files = [re.sub(".raw", "", x) for x in [re.sub("data", "", x) for x in filenames]]

fidx = []
for i in files:
    try:
        idx = int(i)
    except Exception:
        idx = -1
    fidx.append(idx)

df = pd.DataFrame(data = {
  'filenames': filenames,
  'order': fidx,
  'indices': range(0, len(filenames))
})

df = df.sort_values(by = 'order')
df

for f in df['filenames']:
  shutil.copy("data/spain/raw/" + f, "data/spain-mock/raw/" + f)
  print(f)
