import string
import re
from collections import Counter
import sys



def my_function(): #function that prints total sales per item
    with open(r'C:\Users\Raymond\source\repos\groceries\groceries\items.txt') as file: #opens items.txt
        all_words = re.findall(r"[a-zA-Z']+", file.read()) #parses text file 
        all_words = [word.upper()for word in all_words]
        word_counts = Counter() #counts instances
    
    for word in all_words: #loops through file
        word_counts [word] += 1 

    print('Item sales : ') #prints total sales by item in descending order
    for word in word_counts.most_common(30):
        print(word[0], '\t', word[1])

def SearchTotal(cart): #function that searches the list to produce number of sales
	cart = cart.capitalize() #capitalizes first item letter to avoid ambigulity
	with open(r'C:\Users\Raymond\source\repos\groceries\groceries\items.txt') as fp: #opens items.txt
		data = fp.read() #reads items.txt
		sales = data.count(cart) #counts instances of an item
		return sales #sends sale numbers to c++ for printing/formatting

def plotter(): #prepares frequency.dat to interact with c++
    freq_file = open(r'C:\Users\Raymond\source\repos\groceries\groceries\frequency.dat', "w") #opens frequency.dat for writing
    freq_file.write(my_function()) ##writes sale counts to frequency.dat
    freq_file.close() #closes frequency.dat
	


