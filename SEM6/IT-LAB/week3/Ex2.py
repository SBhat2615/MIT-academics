
with open('/Users/siddhartha/Desktop/MIT-academics/SEM6/IT-LAB/week3/file.txt', 'r') as f:
    
    lines = f.read()

    with open('/Users/siddhartha/Desktop/MIT-academics/SEM6/IT-LAB/week3/fileout.txt', 'w+') as fo:
        fo.write(lines[::-1])
        

    f.close()