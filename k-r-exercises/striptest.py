fil = open('ttext\\strip_spaces_start.txt','r')
for line in fil.readlines():
    print(line.strip())
