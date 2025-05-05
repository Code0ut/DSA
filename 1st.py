'''Consider telephone book database of N clients. Make use of a hash table implementation to
quickly look up clients telephone number. Make use of two collision handling techniques and
compare them using number of comparisons required to find a set of telephone numbers'''



class LinearProbing:
	def __init__(self,size):
		self.size=size
		self.table= [None for _ in range(size)]
	
	def hashFunc(self,client):
		return hash(client)%self.size

	def insert(self,key, value):
		index=self.hashFunc(key)
		while(self.table[index] is not None):
			index=(index+1)%self.size
		self.table[index]=(key,value)

	def search(self,key):
		index=self.hashFunc(key)
		comparisons=0
		while self.table[index] is not None and comparisons<=self.size:
			comparisons+=1
			if(self.table[index][0]==key):
				return (1,comparisons)
			index=(index+1)%self.size()
		return (0,comparisons)
	

class Chaining:
	def __init__(self,size):
		self.size=size
		self.table= [[] for _ in range(size)]
	
	def hashFunc(self,client):
		return hash(client)%self.size

	def insert(self,key, value):
		index=self.hashFunc(key)
		self.table[index].append((key,value))

	def search(self,key):
		index=self.hashFunc(key)
		comparisons=0
		if len(self.table[index])!=0:
			for i in self.table[index]:
				comparisons+=1
				if i[0]==key:
					return (1,comparisons)
		return (0,comparisons)

	
def main():
	lb=LinearProbing(10)
	chain=Chaining(10)
	while True:
		print("Enter your choice:\n1.Insert in Linear Probing Hash Table\n2.Insert in Chaining Hash Table\n3.Search key\n4.Exit")
		ch=int(input())
		if(ch==1):
			name=input("Enter client name")
			number=int(input("Enter the number"))
			lb.insert(name,number)
		elif(ch==2):
			name = input("Enter client name")
			number = int(input("Enter the number"))
			chain.insert(name, number)
		elif(ch==3):
			searchKey=input("Enter your search key")
			lbSearch=lb.search(searchKey)
			chainSearch=chain.search(searchKey)
			if(chainSearch[0]==1):
				print("Chaining Comparisons",lbSearch[1])
			else:
				print("Not found in Chaining Table")			

			if(lbSearch[0]==1):
				print("Linear Probing Comparisons",lbSearch[1])
			else:
				print("Not found in Linear Probing Table")
		elif(ch==4):
			break
		else:
			print("invalid Choice!!")
if __name__=='__main__':
	main()
