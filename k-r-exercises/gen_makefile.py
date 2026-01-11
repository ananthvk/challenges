import os
import sys
if os.path.exists('Makefile'):
    print('Makefile already exists, delete it to use this program')
    sys.exit(1)

# Some files or exercises may not exist
# I am adding 25 exercises for each chapter
NCHAPTERS = 8
NEXERCISES = 25

with open('Makefile', 'a') as fil:
    # Generates a makefile for k and r exercises compilation
    for i in range(1, NCHAPTERS+1):
        for j in range(1, NEXERCISES+1):
            fil.write(f'exercise-{i}-{j}: exercise-{i}-{j}.c\n')
            fil.write(f'\tgcc -O0 -ggdb3 -Wall -Wextra -pedantic -w exercise-{i}-{j}.c -o exercise-{i}-{j}\n')
            fil.write(f'run-exercise-{i}-{j}: exercise-{i}-{j}\n')
            fil.write(f'\texercise-{i}-{j}\n')
