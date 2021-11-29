import re

pattern = re.compile("^[0-9]*\.$")

with open("temp.c", "r") as f:
    l = f.readlines()

l1 = []
for i in l:
    t = i.replace("\n", "")
    if pattern.match(t) is None:
        l1.append(t + "\n")

print(l1)

with open("edited.c", "w") as f:
    f.writelines(l1)