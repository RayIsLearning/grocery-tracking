import string
import re
from collections import Counter

path = (r'C:\Users\Raymond\source\repos\groceries\groceries\items.txt')
def count_words(path):
    with open(path) as file:
        all_words = re.findall(r"[a-zA-Z']+", file.read())
        all_words = [word.upper()for word in all_words]
        print('\nTotalWords: ', len(all_words))
    word_counts = Counter()
    for word in all_words:
        word_counts [word] += 1 

    print('Item sales: ')
    for word in word_counts.most_common(30):
        print(word[0], '\t', word[1])



