import string
import re
from collections import Counter
import sys

def count_words():
    with open(r'C:\Users\Raymond\source\repos\groceries\groceries\items.txt') as file:
        all_words = re.findall(r"[a-zA-Z']+", file.read())
        all_words = [word.upper()for word in all_words]
    word_counts = Counter()
    
    for word in all_words:
        word_counts [word] += 1 

    print('Item sales : ')
    for word in word_counts.most_common(30):
        print(word[0], '\t', word[1])

def plotter():
    freq_file = open(r'C:\Users\Raymond\source\repos\groceries\groceries\frequency.dat', "w") 
    freq_file.write(count_words())
    freq_file.close()