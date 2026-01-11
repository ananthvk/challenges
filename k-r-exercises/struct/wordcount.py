import collections
import re
import sys
pattern = r'\w+'
results = None
with(open(sys.argv[1], 'r')) as fil:
    results = re.findall(pattern, fil.read())
ctr = collections.Counter(results)
for i, k in ctr.items():
    print(k,i)
